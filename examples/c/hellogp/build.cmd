rem Create a build directory if it's not already there
mkdir build

rem Change to the build directory
cd build

rem Create the configuration file using cmake
cmake ..

rem Now build the project
cmake --build .

rem All going well, you should now have a DLL in the Debug folder
rem So now copy it to the location where GP can find it

mkdir "C:\Users\Public\Documents\Gig Performer\Extensions"
copy Debug\*.dll "C:\Users\Public\Documents\Gig Performer\Extensions"


