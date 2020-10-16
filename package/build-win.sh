"/mnt/c/Program Files (x86)/WiX Toolset v3.11/bin/candle.exe" -arch x64 SwankyAmp-win64.wxs
"/mnt/c/Program Files (x86)/WiX Toolset v3.11/bin/light.exe" -ext WixUIExtension -cultures:en-us -dWixUILicenseRtf=../Resources/license.rtf SwankyAmp-win64.wixobj
rm -f SwankyAmp-win64.wixobj
rm -f SwankyAmp-win64.wixpdb
