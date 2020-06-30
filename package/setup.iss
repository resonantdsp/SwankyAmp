[Setup]
AppName=ResonantAmp
AppVersion=0.6.2
DefaultDirName={commoncf64}\VST3
DirExistsWarning=no
DisableDirPage=no
DefaultGroupName=ResonantAmp
OutputBaseFilename=ResonantAmp-win64
OutputDir=.
LicenseFile=../LICENSE
Uninstallable = no
 
[Files]
Source: "../Builds\VisualStudio2019\x64\Release\VST3\ResonantAmp.vst3"; Flags: replacesameversion; DestDir: "{app}"

