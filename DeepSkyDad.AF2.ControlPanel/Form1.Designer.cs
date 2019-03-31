namespace DeepSkyDad.AF2.ControlPanel
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.comboComPort = new System.Windows.Forms.ComboBox();
            this.btnChooseFirmware = new System.Windows.Forms.Button();
            this.textBoxFirmwareFile = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.btnUpload = new System.Windows.Forms.Button();
            this.labelTitle = new System.Windows.Forms.Label();
            this.btnExit = new System.Windows.Forms.Button();
            this.groupBoxFirmwareUpgrade = new System.Windows.Forms.GroupBox();
            this.richTextboxOutput = new System.Windows.Forms.RichTextBox();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.checkBoxSyncScroll = new System.Windows.Forms.CheckBox();
            this.btnCopyOutputToClipboard = new System.Windows.Forms.Button();
            this.btnClearOutput = new System.Windows.Forms.Button();
            this.groupBoxManualControl = new System.Windows.Forms.GroupBox();
            this.label3 = new System.Windows.Forms.Label();
            this.comboBoxSpeedMode = new System.Windows.Forms.ComboBox();
            this.label8 = new System.Windows.Forms.Label();
            this.numericIdleTimeout = new System.Windows.Forms.NumericUpDown();
            this.checkBoxReverseDirection = new System.Windows.Forms.CheckBox();
            this.comboCurrentHold = new System.Windows.Forms.ComboBox();
            this.label21 = new System.Windows.Forms.Label();
            this.comboCurrentMove = new System.Windows.Forms.ComboBox();
            this.label10 = new System.Windows.Forms.Label();
            this.comboBoxStepMode = new System.Windows.Forms.ComboBox();
            this.labelTemperature = new System.Windows.Forms.Label();
            this.label25 = new System.Windows.Forms.Label();
            this.comboCoilsMode = new System.Windows.Forms.ComboBox();
            this.label4 = new System.Windows.Forms.Label();
            this.btnMoveContinuousMinus = new System.Windows.Forms.Button();
            this.btnMoveContinuousPlus = new System.Windows.Forms.Button();
            this.label9 = new System.Windows.Forms.Label();
            this.btnStop = new System.Windows.Forms.Button();
            this.labelPosition = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.numericMoveAbsoluteSteps = new System.Windows.Forms.NumericUpDown();
            this.btnMoveAbsoluteGo = new System.Windows.Forms.Button();
            this.label6 = new System.Windows.Forms.Label();
            this.numericMoveRelativeSteps = new System.Windows.Forms.NumericUpDown();
            this.btnMoveRelativeMinus = new System.Windows.Forms.Button();
            this.btnMoveRelativePlus = new System.Windows.Forms.Button();
            this.label5 = new System.Windows.Forms.Label();
            this.label14 = new System.Windows.Forms.Label();
            this.label19 = new System.Windows.Forms.Label();
            this.btnMinus90 = new System.Windows.Forms.Button();
            this.btnMinus180 = new System.Windows.Forms.Button();
            this.btnPlus180 = new System.Windows.Forms.Button();
            this.btnPlus90 = new System.Windows.Forms.Button();
            this.btnConnect = new System.Windows.Forms.Button();
            this.groupBoxWifiSettings = new System.Windows.Forms.GroupBox();
            this.btnSaveWifiSettings = new System.Windows.Forms.Button();
            this.comboWifiMode = new System.Windows.Forms.ComboBox();
            this.textBoxWifiAPPwd = new System.Windows.Forms.TextBox();
            this.label20 = new System.Windows.Forms.Label();
            this.label23 = new System.Windows.Forms.Label();
            this.groupBoxFirmwareUpgrade.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.groupBoxManualControl.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numericIdleTimeout)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericMoveAbsoluteSteps)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericMoveRelativeSteps)).BeginInit();
            this.groupBoxWifiSettings.SuspendLayout();
            this.SuspendLayout();
            // 
            // comboComPort
            // 
            this.comboComPort.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboComPort.FormattingEnabled = true;
            this.comboComPort.Location = new System.Drawing.Point(74, 9);
            this.comboComPort.Name = "comboComPort";
            this.comboComPort.Size = new System.Drawing.Size(75, 21);
            this.comboComPort.TabIndex = 0;
            // 
            // btnChooseFirmware
            // 
            this.btnChooseFirmware.ForeColor = System.Drawing.SystemColors.InfoText;
            this.btnChooseFirmware.Location = new System.Drawing.Point(74, 61);
            this.btnChooseFirmware.Name = "btnChooseFirmware";
            this.btnChooseFirmware.Size = new System.Drawing.Size(75, 23);
            this.btnChooseFirmware.TabIndex = 1;
            this.btnChooseFirmware.Text = "Browse";
            this.btnChooseFirmware.UseVisualStyleBackColor = true;
            this.btnChooseFirmware.Click += new System.EventHandler(this.btnChooseFirmware_Click);
            // 
            // textBoxFirmwareFile
            // 
            this.textBoxFirmwareFile.Location = new System.Drawing.Point(74, 27);
            this.textBoxFirmwareFile.Name = "textBoxFirmwareFile";
            this.textBoxFirmwareFile.ReadOnly = true;
            this.textBoxFirmwareFile.Size = new System.Drawing.Size(212, 20);
            this.textBoxFirmwareFile.TabIndex = 2;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.ForeColor = System.Drawing.SystemColors.Window;
            this.label1.Location = new System.Drawing.Point(16, 12);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(52, 13);
            this.label1.TabIndex = 4;
            this.label1.Text = "COM port";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(15, 30);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(46, 13);
            this.label2.TabIndex = 5;
            this.label2.Text = "DSD file";
            // 
            // btnUpload
            // 
            this.btnUpload.ForeColor = System.Drawing.SystemColors.InfoText;
            this.btnUpload.Location = new System.Drawing.Point(154, 61);
            this.btnUpload.Name = "btnUpload";
            this.btnUpload.Size = new System.Drawing.Size(74, 23);
            this.btnUpload.TabIndex = 3;
            this.btnUpload.Text = "Upload";
            this.btnUpload.UseVisualStyleBackColor = true;
            this.btnUpload.Click += new System.EventHandler(this.btnUpload_Click);
            // 
            // labelTitle
            // 
            this.labelTitle.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.labelTitle.AutoSize = true;
            this.labelTitle.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.labelTitle.Location = new System.Drawing.Point(402, -175);
            this.labelTitle.Name = "labelTitle";
            this.labelTitle.Size = new System.Drawing.Size(172, 13);
            this.labelTitle.TabIndex = 9;
            this.labelTitle.Text = "DSD AF2 Configurator v1.0.0";
            // 
            // btnExit
            // 
            this.btnExit.ForeColor = System.Drawing.SystemColors.InfoText;
            this.btnExit.Location = new System.Drawing.Point(911, 7);
            this.btnExit.Name = "btnExit";
            this.btnExit.Size = new System.Drawing.Size(74, 22);
            this.btnExit.TabIndex = 10;
            this.btnExit.Text = "EXIT";
            this.btnExit.UseVisualStyleBackColor = true;
            this.btnExit.Click += new System.EventHandler(this.btnExit_Click);
            // 
            // groupBoxFirmwareUpgrade
            // 
            this.groupBoxFirmwareUpgrade.Controls.Add(this.btnChooseFirmware);
            this.groupBoxFirmwareUpgrade.Controls.Add(this.textBoxFirmwareFile);
            this.groupBoxFirmwareUpgrade.Controls.Add(this.btnUpload);
            this.groupBoxFirmwareUpgrade.Controls.Add(this.label2);
            this.groupBoxFirmwareUpgrade.ForeColor = System.Drawing.SystemColors.Window;
            this.groupBoxFirmwareUpgrade.Location = new System.Drawing.Point(9, 42);
            this.groupBoxFirmwareUpgrade.Name = "groupBoxFirmwareUpgrade";
            this.groupBoxFirmwareUpgrade.Size = new System.Drawing.Size(311, 138);
            this.groupBoxFirmwareUpgrade.TabIndex = 11;
            this.groupBoxFirmwareUpgrade.TabStop = false;
            this.groupBoxFirmwareUpgrade.Text = "FIRMWARE UPGRADE";
            // 
            // richTextboxOutput
            // 
            this.richTextboxOutput.Location = new System.Drawing.Point(0, 45);
            this.richTextboxOutput.Name = "richTextboxOutput";
            this.richTextboxOutput.ReadOnly = true;
            this.richTextboxOutput.Size = new System.Drawing.Size(361, 364);
            this.richTextboxOutput.TabIndex = 12;
            this.richTextboxOutput.Text = "";
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.checkBoxSyncScroll);
            this.groupBox2.Controls.Add(this.btnCopyOutputToClipboard);
            this.groupBox2.Controls.Add(this.btnClearOutput);
            this.groupBox2.Controls.Add(this.richTextboxOutput);
            this.groupBox2.ForeColor = System.Drawing.SystemColors.Window;
            this.groupBox2.Location = new System.Drawing.Point(612, 42);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(373, 416);
            this.groupBox2.TabIndex = 13;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "OUTPUT";
            // 
            // checkBoxSyncScroll
            // 
            this.checkBoxSyncScroll.AutoSize = true;
            this.checkBoxSyncScroll.Checked = true;
            this.checkBoxSyncScroll.CheckState = System.Windows.Forms.CheckState.Checked;
            this.checkBoxSyncScroll.Location = new System.Drawing.Point(6, 19);
            this.checkBoxSyncScroll.Name = "checkBoxSyncScroll";
            this.checkBoxSyncScroll.Size = new System.Drawing.Size(77, 17);
            this.checkBoxSyncScroll.TabIndex = 133;
            this.checkBoxSyncScroll.Text = "Sync scroll";
            this.checkBoxSyncScroll.UseVisualStyleBackColor = true;
            // 
            // btnCopyOutputToClipboard
            // 
            this.btnCopyOutputToClipboard.ForeColor = System.Drawing.SystemColors.InfoText;
            this.btnCopyOutputToClipboard.Location = new System.Drawing.Point(183, 15);
            this.btnCopyOutputToClipboard.Name = "btnCopyOutputToClipboard";
            this.btnCopyOutputToClipboard.Size = new System.Drawing.Size(102, 22);
            this.btnCopyOutputToClipboard.TabIndex = 13;
            this.btnCopyOutputToClipboard.Text = "Copy to clipboard";
            this.btnCopyOutputToClipboard.UseVisualStyleBackColor = true;
            this.btnCopyOutputToClipboard.Click += new System.EventHandler(this.button2_Click);
            // 
            // btnClearOutput
            // 
            this.btnClearOutput.ForeColor = System.Drawing.SystemColors.InfoText;
            this.btnClearOutput.Location = new System.Drawing.Point(291, 15);
            this.btnClearOutput.Name = "btnClearOutput";
            this.btnClearOutput.Size = new System.Drawing.Size(66, 22);
            this.btnClearOutput.TabIndex = 11;
            this.btnClearOutput.Text = "Clear";
            this.btnClearOutput.UseVisualStyleBackColor = true;
            this.btnClearOutput.Click += new System.EventHandler(this.button1_Click);
            // 
            // groupBoxManualControl
            // 
            this.groupBoxManualControl.Controls.Add(this.label3);
            this.groupBoxManualControl.Controls.Add(this.comboBoxSpeedMode);
            this.groupBoxManualControl.Controls.Add(this.label8);
            this.groupBoxManualControl.Controls.Add(this.numericIdleTimeout);
            this.groupBoxManualControl.Controls.Add(this.checkBoxReverseDirection);
            this.groupBoxManualControl.Controls.Add(this.comboCurrentHold);
            this.groupBoxManualControl.Controls.Add(this.label21);
            this.groupBoxManualControl.Controls.Add(this.comboCurrentMove);
            this.groupBoxManualControl.Controls.Add(this.label10);
            this.groupBoxManualControl.Controls.Add(this.comboBoxStepMode);
            this.groupBoxManualControl.Controls.Add(this.labelTemperature);
            this.groupBoxManualControl.Controls.Add(this.label25);
            this.groupBoxManualControl.Controls.Add(this.comboCoilsMode);
            this.groupBoxManualControl.Controls.Add(this.label4);
            this.groupBoxManualControl.Controls.Add(this.btnMoveContinuousMinus);
            this.groupBoxManualControl.Controls.Add(this.btnMoveContinuousPlus);
            this.groupBoxManualControl.Controls.Add(this.label9);
            this.groupBoxManualControl.Controls.Add(this.btnStop);
            this.groupBoxManualControl.Controls.Add(this.labelPosition);
            this.groupBoxManualControl.Controls.Add(this.label7);
            this.groupBoxManualControl.Controls.Add(this.numericMoveAbsoluteSteps);
            this.groupBoxManualControl.Controls.Add(this.btnMoveAbsoluteGo);
            this.groupBoxManualControl.Controls.Add(this.label6);
            this.groupBoxManualControl.Controls.Add(this.numericMoveRelativeSteps);
            this.groupBoxManualControl.Controls.Add(this.btnMoveRelativeMinus);
            this.groupBoxManualControl.Controls.Add(this.btnMoveRelativePlus);
            this.groupBoxManualControl.Controls.Add(this.label5);
            this.groupBoxManualControl.Controls.Add(this.label14);
            this.groupBoxManualControl.Controls.Add(this.label19);
            this.groupBoxManualControl.Controls.Add(this.btnMinus90);
            this.groupBoxManualControl.Controls.Add(this.btnMinus180);
            this.groupBoxManualControl.Controls.Add(this.btnPlus180);
            this.groupBoxManualControl.Controls.Add(this.btnPlus90);
            this.groupBoxManualControl.ForeColor = System.Drawing.SystemColors.Window;
            this.groupBoxManualControl.Location = new System.Drawing.Point(9, 179);
            this.groupBoxManualControl.Name = "groupBoxManualControl";
            this.groupBoxManualControl.Size = new System.Drawing.Size(597, 279);
            this.groupBoxManualControl.TabIndex = 14;
            this.groupBoxManualControl.TabStop = false;
            this.groupBoxManualControl.Text = "MANUAL CONTROL";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(89, 53);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(38, 13);
            this.label3.TabIndex = 134;
            this.label3.Text = "Speed";
            // 
            // comboBoxSpeedMode
            // 
            this.comboBoxSpeedMode.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxSpeedMode.FormattingEnabled = true;
            this.comboBoxSpeedMode.Items.AddRange(new object[] {
            "Low",
            "Medium",
            "High"});
            this.comboBoxSpeedMode.Location = new System.Drawing.Point(92, 72);
            this.comboBoxSpeedMode.Name = "comboBoxSpeedMode";
            this.comboBoxSpeedMode.Size = new System.Drawing.Size(99, 21);
            this.comboBoxSpeedMode.TabIndex = 133;
            this.comboBoxSpeedMode.SelectedIndexChanged += new System.EventHandler(this.comboBoxSpeedMode_SelectedIndexChanged);
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(194, 53);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(61, 13);
            this.label8.TabIndex = 132;
            this.label8.Text = "Idle timeout";
            // 
            // numericIdleTimeout
            // 
            this.numericIdleTimeout.Location = new System.Drawing.Point(197, 73);
            this.numericIdleTimeout.Maximum = new decimal(new int[] {
            9999999,
            0,
            0,
            0});
            this.numericIdleTimeout.Name = "numericIdleTimeout";
            this.numericIdleTimeout.Size = new System.Drawing.Size(101, 20);
            this.numericIdleTimeout.TabIndex = 131;
            this.numericIdleTimeout.ValueChanged += new System.EventHandler(this.numericIdleTimeout_ValueChanged);
            // 
            // checkBoxReverseDirection
            // 
            this.checkBoxReverseDirection.AutoSize = true;
            this.checkBoxReverseDirection.Location = new System.Drawing.Point(466, 25);
            this.checkBoxReverseDirection.Name = "checkBoxReverseDirection";
            this.checkBoxReverseDirection.Size = new System.Drawing.Size(109, 17);
            this.checkBoxReverseDirection.TabIndex = 130;
            this.checkBoxReverseDirection.Text = "Reverse direction";
            this.checkBoxReverseDirection.UseVisualStyleBackColor = true;
            this.checkBoxReverseDirection.CheckedChanged += new System.EventHandler(this.checkBoxReverseDirection_CheckedChanged);
            // 
            // comboCurrentHold
            // 
            this.comboCurrentHold.FormattingEnabled = true;
            this.comboCurrentHold.Items.AddRange(new object[] {
            "25%",
            "50%",
            "75%",
            "100%"});
            this.comboCurrentHold.Location = new System.Drawing.Point(497, 73);
            this.comboCurrentHold.Name = "comboCurrentHold";
            this.comboCurrentHold.Size = new System.Drawing.Size(78, 21);
            this.comboCurrentHold.TabIndex = 129;
            this.comboCurrentHold.SelectedIndexChanged += new System.EventHandler(this.comboCurrentHold_SelectedIndexChanged);
            // 
            // label21
            // 
            this.label21.AutoSize = true;
            this.label21.Location = new System.Drawing.Point(496, 53);
            this.label21.Name = "label21";
            this.label21.Size = new System.Drawing.Size(70, 13);
            this.label21.TabIndex = 128;
            this.label21.Text = "Current - hold";
            // 
            // comboCurrentMove
            // 
            this.comboCurrentMove.FormattingEnabled = true;
            this.comboCurrentMove.Items.AddRange(new object[] {
            "25%",
            "50%",
            "75%",
            "100%"});
            this.comboCurrentMove.Location = new System.Drawing.Point(395, 73);
            this.comboCurrentMove.Name = "comboCurrentMove";
            this.comboCurrentMove.Size = new System.Drawing.Size(96, 21);
            this.comboCurrentMove.TabIndex = 127;
            this.comboCurrentMove.SelectedIndexChanged += new System.EventHandler(this.comboCurrentMove_SelectedIndexChanged);
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(396, 53);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(76, 13);
            this.label10.TabIndex = 126;
            this.label10.Text = "Current - move";
            // 
            // comboBoxStepMode
            // 
            this.comboBoxStepMode.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxStepMode.FormattingEnabled = true;
            this.comboBoxStepMode.Items.AddRange(new object[] {
            "1/4",
            "1/8"});
            this.comboBoxStepMode.Location = new System.Drawing.Point(20, 72);
            this.comboBoxStepMode.Name = "comboBoxStepMode";
            this.comboBoxStepMode.Size = new System.Drawing.Size(63, 21);
            this.comboBoxStepMode.TabIndex = 82;
            this.comboBoxStepMode.SelectedIndexChanged += new System.EventHandler(this.comboBoxStepMode_SelectedIndexChanged);
            // 
            // labelTemperature
            // 
            this.labelTemperature.AutoSize = true;
            this.labelTemperature.Location = new System.Drawing.Point(234, 25);
            this.labelTemperature.Name = "labelTemperature";
            this.labelTemperature.Size = new System.Drawing.Size(10, 13);
            this.labelTemperature.TabIndex = 125;
            this.labelTemperature.Text = "-";
            // 
            // label25
            // 
            this.label25.AutoSize = true;
            this.label25.Location = new System.Drawing.Point(161, 25);
            this.label25.Name = "label25";
            this.label25.Size = new System.Drawing.Size(67, 13);
            this.label25.TabIndex = 124;
            this.label25.Text = "Temperature";
            // 
            // comboCoilsMode
            // 
            this.comboCoilsMode.FormattingEnabled = true;
            this.comboCoilsMode.Items.AddRange(new object[] {
            "Always on",
            "Idle - coils timeout (ms)"});
            this.comboCoilsMode.Location = new System.Drawing.Point(311, 72);
            this.comboCoilsMode.Name = "comboCoilsMode";
            this.comboCoilsMode.Size = new System.Drawing.Size(79, 21);
            this.comboCoilsMode.TabIndex = 108;
            this.comboCoilsMode.SelectedIndexChanged += new System.EventHandler(this.comboCoilsMode_SelectedIndexChanged);
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(310, 53);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(58, 13);
            this.label4.TabIndex = 107;
            this.label4.Text = "Coils mode";
            // 
            // btnMoveContinuousMinus
            // 
            this.btnMoveContinuousMinus.Enabled = false;
            this.btnMoveContinuousMinus.ForeColor = System.Drawing.SystemColors.InfoText;
            this.btnMoveContinuousMinus.Location = new System.Drawing.Point(447, 208);
            this.btnMoveContinuousMinus.Name = "btnMoveContinuousMinus";
            this.btnMoveContinuousMinus.Size = new System.Drawing.Size(128, 23);
            this.btnMoveContinuousMinus.TabIndex = 101;
            this.btnMoveContinuousMinus.Text = "-";
            this.btnMoveContinuousMinus.UseVisualStyleBackColor = true;
            this.btnMoveContinuousMinus.MouseDown += new System.Windows.Forms.MouseEventHandler(this.btnMoveContinuousMinus_MouseDown);
            this.btnMoveContinuousMinus.MouseUp += new System.Windows.Forms.MouseEventHandler(this.btnMoveContinuousMinus_MouseUp);
            // 
            // btnMoveContinuousPlus
            // 
            this.btnMoveContinuousPlus.Enabled = false;
            this.btnMoveContinuousPlus.ForeColor = System.Drawing.SystemColors.InfoText;
            this.btnMoveContinuousPlus.Location = new System.Drawing.Point(311, 208);
            this.btnMoveContinuousPlus.Name = "btnMoveContinuousPlus";
            this.btnMoveContinuousPlus.Size = new System.Drawing.Size(125, 23);
            this.btnMoveContinuousPlus.TabIndex = 100;
            this.btnMoveContinuousPlus.Text = "+";
            this.btnMoveContinuousPlus.UseVisualStyleBackColor = true;
            this.btnMoveContinuousPlus.MouseDown += new System.Windows.Forms.MouseEventHandler(this.btnMoveContinuousPlus_MouseDown);
            this.btnMoveContinuousPlus.MouseUp += new System.Windows.Forms.MouseEventHandler(this.btnMoveContinuousPlus_MouseUp);
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(308, 184);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(257, 13);
            this.label9.TabIndex = 99;
            this.label9.Text = "Move - continuous (works only if HC is disconnected)";
            // 
            // btnStop
            // 
            this.btnStop.ForeColor = System.Drawing.SystemColors.InfoText;
            this.btnStop.Location = new System.Drawing.Point(270, 249);
            this.btnStop.Name = "btnStop";
            this.btnStop.Size = new System.Drawing.Size(75, 23);
            this.btnStop.TabIndex = 98;
            this.btnStop.Text = "STOP";
            this.btnStop.UseVisualStyleBackColor = true;
            this.btnStop.Click += new System.EventHandler(this.btnStop_Click);
            // 
            // labelPosition
            // 
            this.labelPosition.AutoSize = true;
            this.labelPosition.Location = new System.Drawing.Point(73, 25);
            this.labelPosition.Name = "labelPosition";
            this.labelPosition.Size = new System.Drawing.Size(10, 13);
            this.labelPosition.TabIndex = 97;
            this.labelPosition.Text = "-";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(20, 25);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(44, 13);
            this.label7.TabIndex = 96;
            this.label7.Text = "Position";
            // 
            // numericMoveAbsoluteSteps
            // 
            this.numericMoveAbsoluteSteps.Location = new System.Drawing.Point(21, 208);
            this.numericMoveAbsoluteSteps.Maximum = new decimal(new int[] {
            10000000,
            0,
            0,
            0});
            this.numericMoveAbsoluteSteps.Name = "numericMoveAbsoluteSteps";
            this.numericMoveAbsoluteSteps.Size = new System.Drawing.Size(208, 20);
            this.numericMoveAbsoluteSteps.TabIndex = 95;
            // 
            // btnMoveAbsoluteGo
            // 
            this.btnMoveAbsoluteGo.ForeColor = System.Drawing.SystemColors.InfoText;
            this.btnMoveAbsoluteGo.Location = new System.Drawing.Point(234, 208);
            this.btnMoveAbsoluteGo.Name = "btnMoveAbsoluteGo";
            this.btnMoveAbsoluteGo.Size = new System.Drawing.Size(64, 23);
            this.btnMoveAbsoluteGo.TabIndex = 94;
            this.btnMoveAbsoluteGo.Text = "GO";
            this.btnMoveAbsoluteGo.UseVisualStyleBackColor = true;
            this.btnMoveAbsoluteGo.Click += new System.EventHandler(this.btnMoveAbsoluteGo_Click);
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(16, 184);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(83, 13);
            this.label6.TabIndex = 93;
            this.label6.Text = "Move - absolute";
            // 
            // numericMoveRelativeSteps
            // 
            this.numericMoveRelativeSteps.Location = new System.Drawing.Point(384, 140);
            this.numericMoveRelativeSteps.Maximum = new decimal(new int[] {
            5000,
            0,
            0,
            0});
            this.numericMoveRelativeSteps.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.numericMoveRelativeSteps.Name = "numericMoveRelativeSteps";
            this.numericMoveRelativeSteps.Size = new System.Drawing.Size(123, 20);
            this.numericMoveRelativeSteps.TabIndex = 92;
            this.numericMoveRelativeSteps.Value = new decimal(new int[] {
            200,
            0,
            0,
            0});
            // 
            // btnMoveRelativeMinus
            // 
            this.btnMoveRelativeMinus.ForeColor = System.Drawing.SystemColors.InfoText;
            this.btnMoveRelativeMinus.Location = new System.Drawing.Point(512, 140);
            this.btnMoveRelativeMinus.Name = "btnMoveRelativeMinus";
            this.btnMoveRelativeMinus.Size = new System.Drawing.Size(63, 23);
            this.btnMoveRelativeMinus.TabIndex = 91;
            this.btnMoveRelativeMinus.Text = "-";
            this.btnMoveRelativeMinus.UseVisualStyleBackColor = true;
            this.btnMoveRelativeMinus.Click += new System.EventHandler(this.btnMoveRelativeMinus_Click);
            // 
            // btnMoveRelativePlus
            // 
            this.btnMoveRelativePlus.ForeColor = System.Drawing.SystemColors.InfoText;
            this.btnMoveRelativePlus.Location = new System.Drawing.Point(311, 140);
            this.btnMoveRelativePlus.Name = "btnMoveRelativePlus";
            this.btnMoveRelativePlus.Size = new System.Drawing.Size(67, 23);
            this.btnMoveRelativePlus.TabIndex = 90;
            this.btnMoveRelativePlus.Text = "+";
            this.btnMoveRelativePlus.UseVisualStyleBackColor = true;
            this.btnMoveRelativePlus.Click += new System.EventHandler(this.btnMoveRelativePlus_Click);
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(313, 117);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(77, 13);
            this.label5.TabIndex = 89;
            this.label5.Text = "Move - relative";
            // 
            // label14
            // 
            this.label14.AutoSize = true;
            this.label14.Location = new System.Drawing.Point(17, 114);
            this.label14.Name = "label14";
            this.label14.Size = new System.Drawing.Size(94, 13);
            this.label14.TabIndex = 88;
            this.label14.Text = "Move - fixed angle";
            // 
            // label19
            // 
            this.label19.AutoSize = true;
            this.label19.Location = new System.Drawing.Point(20, 53);
            this.label19.Name = "label19";
            this.label19.Size = new System.Drawing.Size(29, 13);
            this.label19.TabIndex = 87;
            this.label19.Text = "Step";
            // 
            // btnMinus90
            // 
            this.btnMinus90.ForeColor = System.Drawing.SystemColors.InfoText;
            this.btnMinus90.Location = new System.Drawing.Point(92, 140);
            this.btnMinus90.Name = "btnMinus90";
            this.btnMinus90.Size = new System.Drawing.Size(66, 23);
            this.btnMinus90.TabIndex = 82;
            this.btnMinus90.Text = "-90  deg";
            this.btnMinus90.UseVisualStyleBackColor = true;
            this.btnMinus90.Click += new System.EventHandler(this.btnMinus90_Click);
            // 
            // btnMinus180
            // 
            this.btnMinus180.ForeColor = System.Drawing.SystemColors.InfoText;
            this.btnMinus180.Location = new System.Drawing.Point(234, 140);
            this.btnMinus180.Name = "btnMinus180";
            this.btnMinus180.Size = new System.Drawing.Size(64, 23);
            this.btnMinus180.TabIndex = 81;
            this.btnMinus180.Text = "-180 deg";
            this.btnMinus180.UseVisualStyleBackColor = true;
            this.btnMinus180.Click += new System.EventHandler(this.btnMinus180_Click);
            // 
            // btnPlus180
            // 
            this.btnPlus180.ForeColor = System.Drawing.SystemColors.InfoText;
            this.btnPlus180.Location = new System.Drawing.Point(164, 140);
            this.btnPlus180.Name = "btnPlus180";
            this.btnPlus180.Size = new System.Drawing.Size(64, 23);
            this.btnPlus180.TabIndex = 80;
            this.btnPlus180.Text = "+180  deg";
            this.btnPlus180.UseVisualStyleBackColor = true;
            this.btnPlus180.Click += new System.EventHandler(this.btnPlus180_Click);
            // 
            // btnPlus90
            // 
            this.btnPlus90.ForeColor = System.Drawing.SystemColors.InfoText;
            this.btnPlus90.Location = new System.Drawing.Point(18, 140);
            this.btnPlus90.Name = "btnPlus90";
            this.btnPlus90.Size = new System.Drawing.Size(68, 23);
            this.btnPlus90.TabIndex = 78;
            this.btnPlus90.Text = "+90 deg";
            this.btnPlus90.UseVisualStyleBackColor = true;
            this.btnPlus90.Click += new System.EventHandler(this.btnPlus90_Click);
            // 
            // btnConnect
            // 
            this.btnConnect.ForeColor = System.Drawing.SystemColors.InfoText;
            this.btnConnect.Location = new System.Drawing.Point(155, 8);
            this.btnConnect.Name = "btnConnect";
            this.btnConnect.Size = new System.Drawing.Size(93, 23);
            this.btnConnect.TabIndex = 79;
            this.btnConnect.Text = "Connect";
            this.btnConnect.UseVisualStyleBackColor = true;
            this.btnConnect.Click += new System.EventHandler(this.connectBtn_Click);
            // 
            // groupBoxWifiSettings
            // 
            this.groupBoxWifiSettings.Controls.Add(this.btnSaveWifiSettings);
            this.groupBoxWifiSettings.Controls.Add(this.comboWifiMode);
            this.groupBoxWifiSettings.Controls.Add(this.textBoxWifiAPPwd);
            this.groupBoxWifiSettings.Controls.Add(this.label20);
            this.groupBoxWifiSettings.Controls.Add(this.label23);
            this.groupBoxWifiSettings.ForeColor = System.Drawing.SystemColors.Window;
            this.groupBoxWifiSettings.Location = new System.Drawing.Point(326, 42);
            this.groupBoxWifiSettings.Name = "groupBoxWifiSettings";
            this.groupBoxWifiSettings.Size = new System.Drawing.Size(280, 138);
            this.groupBoxWifiSettings.TabIndex = 15;
            this.groupBoxWifiSettings.TabStop = false;
            this.groupBoxWifiSettings.Text = "WIFI SETTINGS";
            // 
            // btnSaveWifiSettings
            // 
            this.btnSaveWifiSettings.ForeColor = System.Drawing.SystemColors.InfoText;
            this.btnSaveWifiSettings.Location = new System.Drawing.Point(94, 99);
            this.btnSaveWifiSettings.Name = "btnSaveWifiSettings";
            this.btnSaveWifiSettings.Size = new System.Drawing.Size(74, 23);
            this.btnSaveWifiSettings.TabIndex = 8;
            this.btnSaveWifiSettings.Text = "Save";
            this.btnSaveWifiSettings.UseVisualStyleBackColor = true;
            this.btnSaveWifiSettings.Click += new System.EventHandler(this.btnSaveWifiSettings_Click);
            // 
            // comboWifiMode
            // 
            this.comboWifiMode.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboWifiMode.FormattingEnabled = true;
            this.comboWifiMode.Items.AddRange(new object[] {
            "OFF",
            "AP"});
            this.comboWifiMode.Location = new System.Drawing.Point(94, 26);
            this.comboWifiMode.Name = "comboWifiMode";
            this.comboWifiMode.Size = new System.Drawing.Size(155, 21);
            this.comboWifiMode.TabIndex = 80;
            // 
            // textBoxWifiAPPwd
            // 
            this.textBoxWifiAPPwd.Location = new System.Drawing.Point(94, 61);
            this.textBoxWifiAPPwd.Name = "textBoxWifiAPPwd";
            this.textBoxWifiAPPwd.Size = new System.Drawing.Size(155, 20);
            this.textBoxWifiAPPwd.TabIndex = 11;
            // 
            // label20
            // 
            this.label20.AutoSize = true;
            this.label20.ForeColor = System.Drawing.SystemColors.Window;
            this.label20.Location = new System.Drawing.Point(17, 29);
            this.label20.Name = "label20";
            this.label20.Size = new System.Drawing.Size(34, 13);
            this.label20.TabIndex = 81;
            this.label20.Text = "Mode";
            // 
            // label23
            // 
            this.label23.AutoSize = true;
            this.label23.Location = new System.Drawing.Point(17, 64);
            this.label23.Name = "label23";
            this.label23.Size = new System.Drawing.Size(69, 13);
            this.label23.TabIndex = 10;
            this.label23.Text = "AP password";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.ActiveCaptionText;
            this.ClientSize = new System.Drawing.Size(995, 465);
            this.Controls.Add(this.groupBoxWifiSettings);
            this.Controls.Add(this.comboComPort);
            this.Controls.Add(this.groupBoxManualControl);
            this.Controls.Add(this.btnExit);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.groupBoxFirmwareUpgrade);
            this.Controls.Add(this.labelTitle);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.btnConnect);
            this.ForeColor = System.Drawing.SystemColors.Window;
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "Form1";
            this.groupBoxFirmwareUpgrade.ResumeLayout(false);
            this.groupBoxFirmwareUpgrade.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.groupBoxManualControl.ResumeLayout(false);
            this.groupBoxManualControl.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numericIdleTimeout)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericMoveAbsoluteSteps)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericMoveRelativeSteps)).EndInit();
            this.groupBoxWifiSettings.ResumeLayout(false);
            this.groupBoxWifiSettings.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ComboBox comboComPort;
        private System.Windows.Forms.Button btnChooseFirmware;
        private System.Windows.Forms.TextBox textBoxFirmwareFile;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Button btnUpload;
        private System.Windows.Forms.Label labelTitle;
        private System.Windows.Forms.Button btnExit;
        private System.Windows.Forms.GroupBox groupBoxFirmwareUpgrade;
        private System.Windows.Forms.RichTextBox richTextboxOutput;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.Button btnCopyOutputToClipboard;
        private System.Windows.Forms.Button btnClearOutput;
        private System.Windows.Forms.GroupBox groupBoxManualControl;
        private System.Windows.Forms.ComboBox comboCoilsMode;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Button btnMoveContinuousMinus;
        private System.Windows.Forms.Button btnMoveContinuousPlus;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.Button btnStop;
        private System.Windows.Forms.Label labelPosition;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.NumericUpDown numericMoveAbsoluteSteps;
        private System.Windows.Forms.Button btnMoveAbsoluteGo;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.NumericUpDown numericMoveRelativeSteps;
        private System.Windows.Forms.Button btnMoveRelativeMinus;
        private System.Windows.Forms.Button btnMoveRelativePlus;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label14;
        private System.Windows.Forms.Label label19;
        private System.Windows.Forms.Button btnMinus90;
        private System.Windows.Forms.Button btnMinus180;
        private System.Windows.Forms.Button btnPlus180;
        private System.Windows.Forms.Button btnConnect;
        private System.Windows.Forms.Button btnPlus90;
        private System.Windows.Forms.Label labelTemperature;
        private System.Windows.Forms.Label label25;
        private System.Windows.Forms.GroupBox groupBoxWifiSettings;
        private System.Windows.Forms.Button btnSaveWifiSettings;
        private System.Windows.Forms.ComboBox comboWifiMode;
        private System.Windows.Forms.TextBox textBoxWifiAPPwd;
        private System.Windows.Forms.Label label20;
        private System.Windows.Forms.Label label23;
        private System.Windows.Forms.ComboBox comboBoxStepMode;
        private System.Windows.Forms.ComboBox comboCurrentHold;
        private System.Windows.Forms.Label label21;
        private System.Windows.Forms.ComboBox comboCurrentMove;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.CheckBox checkBoxReverseDirection;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.NumericUpDown numericIdleTimeout;
        private System.Windows.Forms.CheckBox checkBoxSyncScroll;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.ComboBox comboBoxSpeedMode;
    }
}

