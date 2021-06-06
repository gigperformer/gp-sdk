::Create a build directory if it's not already there
mkdir build

::Change to the build directory
cd build

::Create the configuration file using cmake
cmake ..

::Now build the project in DEBUG mode.
cmake --build .

::For RELEASE mode please execute this instead
::cmake --build . --config Release

::All going well, you should now have a DLL in the Debug folder
::So now copy it to the location where GP can find it

mkdir "C:\Users\Public\Documents\Gig Performer\Extensions"
copy Debug\*.dll "%PUBLIC%\Documents\Gig Performer\Extensions"

::For RELEASE build please replace the "Debug" folder reference with "Release"

::Go back to the starting folder
cd ..

rem
rem ********************************************
rem Extension built and installed into "%PUBLIC%\Documents\Gig Performer\Extensions"
rem ********************************************

