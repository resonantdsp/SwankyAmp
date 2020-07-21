[Setup]
AppName=SwankyAmp
AppVersion=0.8.0
DefaultDirName={commoncf64}\VST3
DirExistsWarning=no
DisableDirPage=no
DefaultGroupName=SwankyAmp
OutputBaseFilename=SwankyAmp-win64
OutputDir=.
LicenseFile=../LICENSE
Uninstallable = no
 
[Files]
Source: "../Builds\VisualStudio2019\x64\Release\VST3\SwankyAmp.vst3"; Flags: replacesameversion; DestDir: "{app}"

