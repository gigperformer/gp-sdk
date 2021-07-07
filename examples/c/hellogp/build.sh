#!/bin/sh

targetFolder='/Users/Shared/Gig Performer/Extensions'

if ! test -d "$targetFolder"; then
   mkdir -p "$targetFolder"
   echo "Creating target directory for library"
fi


#Get rid of all the DLLs in there so we can do a clean test
#echo "Removing existing libraries"
#rm -rf "$targetFolder"/*


if ! test -d build; then
   mkdir build
fi
cd build
cmake ..
cmake --build . --config Release
mv *.dylib "$targetFolder"