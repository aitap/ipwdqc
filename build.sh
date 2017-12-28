#!/bin/sh -ev
premake4 clean
premake4 --iup-inc=$HOME/local/iup/include --iup-lib="$(echo "$HOME/local/iup/lib/Linux"??_??)" gmake
make config=release verbose=1
cp gui ipwqgen
make clean
premake4 clean
# aaaargh, Debian version has hardcoded "windres"
../premake-4.x/bin/release/premake4 --iup-inc=$HOME/local/windows/libs/iup/include --iup-lib=$HOME/local/windows/libs/iup --os=windows gmake
make CC=i686-w64-mingw32-gcc RESCOMP=i686-w64-mingw32-windres config=release verbose=1
cp gui.exe ipwqgen.exe
make clean
premake4 clean
