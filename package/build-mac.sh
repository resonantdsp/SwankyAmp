#!/bin/bash
set -e

cp ../Resources/dmg-bg.png dmg-vst3/.bg.png
cp ../Resources/dmg-bg.png dmg-au/.bg.png

cp -r ../Builds/MacOSX/build/Release/SwankyAmp.vst3 dmg-vst3/
cp -r ../Builds/MacOSX/build/Release/SwankyAmp.component dmg-au/

hdiutil create -fs "Case-sensitive Journaled HFS+" -format UDRW -srcfolder dmg-vst3 dmg-vst3.dmg
hdiutil create -fs "Case-sensitive Journaled HFS+" -format UDRW -srcfolder dmg-au dmg-au.dmg

read -r -n 1 -p "Set DMG style then press any key to continue"

hdiutil convert -format UDRO -o SwankyAmp-vst3.dmg dmg-vst3.dmg
hdiutil convert -format UDRO -o SwankyAmp-au.dmg dmg-au.dmg
