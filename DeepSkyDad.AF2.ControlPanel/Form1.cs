using CliWrap;
using CliWrap.Services;
using Syroot.Windows.IO;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Drawing.Text;
using System.IO;
using System.IO.Compression;
using System.IO.Ports;
using System.Linq;
using System.Reflection;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;
using static DeepSkyDad.AF2.ControlPanel.FirmwareUpdateService;
using static DeepSkyDad.AF2.ControlPanel.SerialService;

namespace DeepSkyDad.AF2.ControlPanel
{
    public partial class Form1 : Form
    {
        private static PrivateFontCollection _fonts = new PrivateFontCollection();

        private const int WM_NCHITTEST = 0x84;
        private const int HTCLIENT = 0x1;
        private const int HTCAPTION = 0x2;

        private SerialService _serialService;
        private FirmwareUpdateService _firmwareUpdateService;

        private bool _isConnected;
        private bool _isUploadingFirmware;

        ///
        /// Handling the window messages
        ///
        protected override void WndProc(ref Message message)
        {
            base.WndProc(ref message);

            if (message.Msg == WM_NCHITTEST && (int)message.Result == HTCLIENT)
                message.Result = (IntPtr)HTCAPTION;
        }

        public Form1()
        {
            InitializeComponent();

            //var test = Assembly.GetExecutingAssembly().GetManifestResourceNames();
            AddFontFromResource("DeepSkyDad.AF2.ControlPanel.EmbeddedFiles.TitilliumWeb-Light.ttf");
            AddFontFromResource("DeepSkyDad.AF2.ControlPanel.EmbeddedFiles.AlegreyaSansSC-Bold.ttf");
            //_fonts.AddFontFile("TitilliumWeb-Light.ttf");
            //_fonts.AddFontFile("AlegreyaSansSC-Bold.ttf");

            this.Icon = new Icon(Assembly.GetExecutingAssembly().GetManifestResourceStream("DeepSkyDad.AF2.ControlPanel.EmbeddedFiles.favicon.ico"));

            this.ControlBox = false;
            this.Text = String.Empty;
            this.FormBorderStyle = FormBorderStyle.FixedSingle;
            this.Font = new Font(_fonts.Families[1], 9, FontStyle.Regular);
            this.ForeColor = Color.White;
            this.BackColor = Color.FromArgb(24, 24, 24);

            this.labelTitle.Font = new Font(_fonts.Families[0], 12, FontStyle.Bold);
            this.labelTitle.Left = (this.ClientSize.Width - this.labelTitle.Width) / 2;
            this.labelTitle.Top = 20;
            this.labelTitle.Text = "DSD AF2 Control Panel v1.0.0";

            this.comboComPort.DropDown += comPortCombo_DropDown;

            _serialService = new SerialService(
                (SerialServiceStatus status) =>
                {
                    if (status == SerialServiceStatus.Connected)
                    {
                        _isConnected = true;
                        btnConnect.Text = "Disconnect";
                        richTextboxOutput.Invoke(new AppendOutputTextDelegate(AppendOutputText), new Object[] { "AF2 Connected", false });
                        RefreshUI();
                        ReadFocuserState();
                    }
                    else
                    {
                        _isConnected = false;
                        btnConnect.Text = "Connect";
                        richTextboxOutput.Invoke(new AppendOutputTextDelegate(AppendOutputText), new Object[] { "AF2 Disconnected", false });
                        RefreshUI();
                    }
                },
                (string serialDataReceived, bool isError) =>
                {
                    richTextboxOutput.Invoke(new AppendOutputTextDelegate(AppendOutputText), new Object[] { serialDataReceived, isError });
                }
            );

            _firmwareUpdateService = new FirmwareUpdateService(
                (FirmwareUpdateStatus status) =>
                {
                    _isUploadingFirmware = false;
                    if (status == FirmwareUpdateStatus.Uploading)
                    {
                        _isUploadingFirmware = true;
                        richTextboxOutput.Invoke(new AppendOutputTextDelegate(AppendOutputText), new Object[] { "UPLOADING...", false });
                    }
                    else if (status == FirmwareUpdateStatus.Successful)
                    {
                        richTextboxOutput.Invoke(new AppendOutputTextDelegate(AppendOutputText), new Object[] { "UPLOAD SUCCESSFUL!", false });
                    }
                    else if (status == FirmwareUpdateStatus.Error)
                    {
                        richTextboxOutput.Invoke(new AppendOutputTextDelegate(AppendOutputText), new Object[] { "FIRMWARE UPLOAD FAILED!", true});
                    }

                    RefreshUI();
                },
                (string text, bool isError) =>
                {
                    richTextboxOutput.Invoke(new AppendOutputTextDelegate(AppendOutputText), new Object[] { text, isError });
                }
            );

            richTextboxOutput.TextChanged += (object sender, EventArgs e) =>
            {
                if (!checkBoxSyncScroll.Checked)
                    return;
                richTextboxOutput.SelectionStart = richTextboxOutput.Text.Length;
                richTextboxOutput.ScrollToCaret();
            };

            ClearUI();
            RefreshUI();

            var timer = new System.Windows.Forms.Timer();
            timer.Interval = (500);
            timer.Tick += new EventHandler((object sender, EventArgs e) =>
            {
                ReadPositionAndTemperature(false, false);
            });
            timer.Start();
        }

        private void comPortCombo_DropDown(object sender, EventArgs e)
        {
            this.comboComPort.Items.Clear();
            var i = 0;
            foreach (var port in SerialPort.GetPortNames())
            {
                this.comboComPort.Items.Insert(i, port);
                i++;
            }
        }

        private void btnChooseFirmware_Click(object sender, EventArgs e)
        {
            OpenFileDialog theDialog = new OpenFileDialog();
            theDialog.Title = "Choose firmware .dsd file";
            theDialog.Filter = "DSD files|*.dsd";
            theDialog.InitialDirectory = KnownFolders.Downloads.Path;
            if (theDialog.ShowDialog() == DialogResult.OK)
            {
                this.textBoxFirmwareFile.Text = theDialog.FileName.ToString();
            }
        }

        private async void btnUpload_Click(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(this.comboComPort.Text))
            {
                AppendOutputText("Please, select COM port", true);
                return;
            }
            else if (string.IsNullOrWhiteSpace(this.textBoxFirmwareFile.Text))
            {
                AppendOutputText("Please, select firmare DSD file", true);
                return;
            }

            await _firmwareUpdateService.UpoloadFirmware(this.comboComPort.Text, this.textBoxFirmwareFile.Text);
        }

        private void btnExit_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }

        private static void AddFontFromResource(string fontResourceName)
        {
            var fontBytes = GetFontResourceBytes(fontResourceName);
            var fontData = Marshal.AllocCoTaskMem(fontBytes.Length);
            Marshal.Copy(fontBytes, 0, fontData, fontBytes.Length);
            _fonts.AddMemoryFont(fontData, fontBytes.Length);
            Marshal.FreeCoTaskMem(fontData);
        }

        private static byte[] GetFontResourceBytes(string fontResourceName)
        {
            var resourceStream = Assembly.GetExecutingAssembly().GetManifestResourceStream(fontResourceName);
            if (resourceStream == null)
                throw new Exception(string.Format("Unable to find font '{0}' in embedded resources.", fontResourceName));
            var fontBytes = new byte[resourceStream.Length];
            resourceStream.Read(fontBytes, 0, (int)resourceStream.Length);
            resourceStream.Close();
            return fontBytes;
        }

        private void RefreshUI()
        {
            comboComPort.Enabled = !_isConnected && !_isUploadingFirmware;
            btnExit.Enabled = !_isUploadingFirmware;

            btnChooseFirmware.Enabled = !_isUploadingFirmware && !_isConnected;
            textBoxFirmwareFile.Enabled = !_isUploadingFirmware && !_isConnected;
            btnUpload.Enabled = !_isUploadingFirmware && !_isConnected;

            foreach (Control c in groupBoxManualControl.Controls)
            {
                if (c.GetType() == typeof(Label))
                    continue;
                c.Enabled = _isConnected;
            }

            foreach (Control c in groupBoxWifiSettings.Controls)
            {
                if (c.GetType() == typeof(Label))
                    continue;
                c.Enabled = _isConnected;
            }

            if (!_isConnected)
            {
                comboWifiMode.SelectedIndex = -1;
                textBoxWifiAPPwd.Text = string.Empty;
            }
        }

        private void ClearUI()
        {
            labelPosition.Text = "-";
            labelTemperature.Text = "-";
            comboBoxStepMode.Text = null;
            numericIdleTimeout.Value = 0;
            comboCoilsMode.Text = null;
            comboCurrentHold.Text = null;
            comboCurrentMove.Text = null;
            comboCurrentHold.Text = null;
            numericMoveAbsoluteSteps.Value = 0;
        }

        private async void ReadFocuserState()
        {
            var wifiMode = await _serialService.SendCommand("[GWFM]");
            switch(wifiMode)
            {
                case "0":
                    wifiMode = "OFF";
                    break;
                case "1":
                    wifiMode = "AP";
                    break;
                case "2":
                    wifiMode = "STA";
                    break;
                case "3":
                    wifiMode = "AP-STA";
                    break;
                default:
                    wifiMode = "AP";
                    break;
            }
            comboWifiMode.Text = wifiMode;

            textBoxWifiAPPwd.Text = await _serialService.SendCommand("[GWFP]");

            await ReadPositionAndTemperature();

            checkBoxReverseDirection.Checked = await _serialService.SendCommand("[MGRV]") == "1";

            var stepMode = await _serialService.SendCommand("[MGST]");
            switch (stepMode)
            {
                case "1":
                    stepMode = "1";
                    break;
                case "2":
                    stepMode = "1/2";
                    break;
                case "4":
                    stepMode = "1/4";
                    break;
                case "8":
                    stepMode = "1/8";
                    break;
                default:
                    stepMode = "1/8";
                    break;
            }
            comboBoxStepMode.Text = stepMode;

            var speedMode = await _serialService.SendCommand("[MGSP]");
            switch (speedMode)
            {
                case "1":
                    speedMode = "Low";
                    break;
                case "2":
                    speedMode = "Medium";
                    break;
                case "3":
                    speedMode = "High";
                    break;
                default:
                    speedMode = "Low";
                    break;
            }
            comboBoxSpeedMode.Text = speedMode;

            var coilsMode = await _serialService.SendCommand("[MGCL]");
            switch (coilsMode)
            {
                case "1":
                    coilsMode = "Always on";
                    break;
                case "2":
                    coilsMode = "Idle - coils timeout (ms)";
                    break;
                default:
                    coilsMode = "Always on";
                    break;
            }
            comboCoilsMode.Text = coilsMode;

            comboCurrentMove.Text = await _serialService.SendCommand("[MGCM%]");
            comboCurrentHold.Text = await _serialService.SendCommand("[MGCH%]");
            numericIdleTimeout.Value = Convert.ToInt32(await _serialService.SendCommand("[MGIC]"));
        }

        private async Task<bool> ReadPositionAndTemperature(bool isRefreshAbsolutePositionField = true, bool isOutputSerial = true)
        {
            if (!_isConnected)
                return false;

            var position = await _serialService.SendCommand("[GPOS]", true, isOutputSerial);
            var tmpC = await _serialService.SendCommand("[GTMC]", true, isOutputSerial);

            labelPosition.Text = position;
            if(isRefreshAbsolutePositionField)
                numericMoveAbsoluteSteps.Value = Convert.ToInt32(position);
         
            labelTemperature.Text = tmpC == "-127.00" ? "Disconnected" : tmpC;
            return true;
        }

        private void MoveForAngle(int angle, string stepMode)
        {
            int steps;
            switch (stepMode)
            {
                case "1":
                    steps = 200;
                    break;
                case "1/2":
                    steps = 400;
                    break;
                case "1/4":
                    steps = 800;
                    break;
                case "1/8":
                    steps = 1600;
                    break;
                default:
                    steps = 200;
                    break;
            }

            MoveForSteps(steps / (360 / angle));
        }

        private async void MoveForSteps(int steps)
        {
            var pos = Convert.ToInt32(await _serialService.SendCommand("[GPOS]"));
            var target = pos + steps;

            await _serialService.SendCommand($"[STRG{target}]");
            await _serialService.SendCommand("[MSMV]");
        }

        public delegate void AppendOutputTextDelegate(string text, bool isError);

        public void AppendOutputText(string text)
        {
            AppendOutputText(text, false);
        }

        public void AppendOutputText(String text, bool isError)
        {
            richTextboxOutput.AppendText($"{text}\r\n", isError ? Color.Red : Color.Green);
        }

        private void button2_Click(object sender, EventArgs e)
        {
            Clipboard.SetText(richTextboxOutput.Text);
        }

        private void button1_Click(object sender, EventArgs e)
        {
            richTextboxOutput.Text = string.Empty;
        }

        private void connectBtn_Click(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(this.comboComPort.Text))
            {
                AppendOutputText("Please choose COM port", true);
                return;
            }

            try
            {
                if (_isConnected)
                {
                    _serialService.Disconnect();
                    ClearUI();
                }
                else
                {
                    _serialService.Connect(this.comboComPort.Text);
                }
            }
            catch (Exception ex)
            {
                AppendOutputText(ex.Message, true);
            }

            RefreshUI();
        }

        private async void btnSaveWifiSettings_Click(object sender, EventArgs e)
        {
            if(string.IsNullOrWhiteSpace(textBoxWifiAPPwd.Text) || textBoxWifiAPPwd.Text.Length < 8)
            {
                AppendOutputText("Please enter Wifi AP password that is at least 8 characters long");
                return;
            }

            var wifiMode = comboWifiMode.Text;
            switch (wifiMode)
            {
                case "OFF":
                    wifiMode = "0";
                    break;
                case "AP":
                    wifiMode = "1";
                    break;
                case "STA":
                    wifiMode = "2";
                    break;
                case "AP-STA":
                    wifiMode = "3";
                    break;
                default:
                    wifiMode = "1";
                    break;
            }

            await _serialService.SendCommand($"[SWFM{wifiMode}]");
            await _serialService.SendCommand($"[SWFP{textBoxWifiAPPwd.Text}]");
        }

        private async void comboBoxStepMode_SelectedIndexChanged(object sender, EventArgs e)
        {
            string stepMode;
            switch (comboBoxStepMode.Text)
            {
                case "1":
                    stepMode = "1";
                    break;
                case "1/2":
                    stepMode = "2";
                    break;
                case "1/4":
                    stepMode = "4";
                    break;
                case "1/8":
                    stepMode = "8";
                    break;
                default:
                    stepMode = "8";
                    break;
            }

            await _serialService.SendCommand($"[MSST{stepMode}]");
        }

        private async void comboBoxSpeedMode_SelectedIndexChanged(object sender, EventArgs e)
        {
            string speedMode;
            switch (comboBoxSpeedMode.Text)
            {
                case "Low":
                    speedMode = "1";
                    break;
                case "Medium":
                    speedMode = "2";
                    break;
                case "High":
                    speedMode = "3";
                    break;
                default:
                    speedMode = "1";
                    break;
            }

            await _serialService.SendCommand($"[MSSP{speedMode}]");
        }

        private async void numericIdleTimeout_ValueChanged(object sender, EventArgs e)
        {
            await _serialService.SendCommand($"[MSIC{numericIdleTimeout.Value}]");
        }

        private async void comboCoilsMode_SelectedIndexChanged(object sender, EventArgs e)
        {
            string coilsMode;
            switch (comboCoilsMode.Text)
            {
                case "Always on":
                    coilsMode = "1";
                    break;
                case "Idle - coils timeout (ms)":
                    coilsMode = "2";
                    break;
                default:
                    coilsMode = "1";
                    break;
            }

            await _serialService.SendCommand($"[MSCL{coilsMode}]");
        }

        private async void comboCurrentMove_SelectedIndexChanged(object sender, EventArgs e)
        {
            await _serialService.SendCommand($"[MSCM{comboCurrentMove.Text}]");
        }

        private async void comboCurrentHold_SelectedIndexChanged(object sender, EventArgs e)
        {
            await _serialService.SendCommand($"[MSCH{comboCurrentMove.Text}]");
        }
        private void btnPlus90_Click(object sender, EventArgs e)
        {
            var stepMode = comboBoxStepMode.Text;
            MoveForAngle(90, stepMode);
        }

        private void btnMinus90_Click(object sender, EventArgs e)
        {
            var stepMode = comboBoxStepMode.Text;
            MoveForAngle(-90, stepMode);
        }

        private void btnPlus180_Click(object sender, EventArgs e)
        {
            var stepMode = comboBoxStepMode.Text;
            MoveForAngle(180, stepMode);
        }

        private void btnMinus180_Click(object sender, EventArgs e)
        {
            var stepMode = comboBoxStepMode.Text;
            MoveForAngle(-180, stepMode);
        }

        private void btnMoveRelativePlus_Click(object sender, EventArgs e)
        {
            MoveForSteps((int)numericMoveRelativeSteps.Value);
        }

        private void btnMoveRelativeMinus_Click(object sender, EventArgs e)
        {
            MoveForSteps(-1*(int)numericMoveRelativeSteps.Value);
        }

        private async void btnMoveAbsoluteGo_Click(object sender, EventArgs e)
        {
            await _serialService.SendCommand($"[STRG{(int)numericMoveAbsoluteSteps.Value}]");
            await _serialService.SendCommand("[MSMV]");
        }

        private async void btnStop_Click(object sender, EventArgs e)
        {
            await _serialService.SendCommand("[STOP]");
        }

        private async void btnMoveContinuousPlus_MouseDown(object sender, MouseEventArgs e)
        {
            await _serialService.SendCommand("[MMCC]");
        }

        private async void btnMoveContinuousPlus_MouseUp(object sender, MouseEventArgs e)
        {
            await _serialService.SendCommand("[STOP]");
        }

        private async void btnMoveContinuousMinus_MouseDown(object sender, MouseEventArgs e)
        {
            await _serialService.SendCommand("[MMCW]");
        }

        private async void btnMoveContinuousMinus_MouseUp(object sender, MouseEventArgs e)
        {
            await _serialService.SendCommand("[STOP]");
        }

        private async void checkBoxReverseDirection_CheckedChanged(object sender, EventArgs e)
        {
            await _serialService.SendCommand($"[MSRV{(checkBoxReverseDirection.Checked == true ? 1 : 0)}]");
        }
    }

    public static class RichTextBoxExtensions
    {
        public static void AppendText(this RichTextBox box, string text, Color color)
        {
            box.SelectionStart = box.TextLength;
            box.SelectionLength = 0;

            box.SelectionColor = color;
            box.AppendText(text);
            box.SelectionColor = box.ForeColor;
        }
    }
}
