#!/bin/sh -ev
premake4 clean
premake4 --iup-inc=$HOME/local/iup/include --iup-lib="$(echo "$HOME/local/iup/lib/Linux"??_??)" gmake
make config=release verbose=1
mv pwq-gui ipwqgen
premake4 clean
# aaaargh, Debian version has hardcoded "windres"
../premake-4.x/bin/release/premake4 --iup-inc=$HOME/local/windows/libs/iup64/include --iup-lib=$HOME/local/windows/libs/iup64 --os=windows gmake
make CC=x86_64-w64-mingw32-gcc RESCOMP=x86_64-w64-mingw32-windres config=release verbose=1
mv pwq-gui.exe ipwqgen64.exe
premake4 clean
../premake-4.x/bin/release/premake4 --iup-inc=$HOME/local/windows/libs/iup/include --iup-lib=$HOME/local/windows/libs/iup --os=windows --winxp gmake
make CC=i686-w64-mingw32-gcc RESCOMP=i686-w64-mingw32-windres config=release verbose=1
mv pwq-gui.exe ipwqgen32.exe
premake4 clean
