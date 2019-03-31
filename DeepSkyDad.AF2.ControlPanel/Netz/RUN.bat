netz -s -z -so ../bin/Release/DeepSkyDad.AF2.ControlPanel.exe ../bin/Release/CliWrap.dll ../bin/Release/Syroot.KnownFolders.dll
xcopy "../bin/Release/Esptool" "../bin/Release/DeepSkyDad.AF2.ControlPanel.exe.netz/Esptool" /e /i /h
cd "../bin/Release/DeepSkyDad.AF2.ControlPanel.exe.netz"
del "AF2 Control Panel.exe"
rename "DeepSkyDad.AF2.ControlPanel.exe" "AF2 Control Panel.exe"
