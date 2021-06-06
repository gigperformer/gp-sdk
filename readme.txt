For Windows - please use "Developer Command Prompts for VS 2019"

The above should set all required environment variables, but in some cases you may need to run this batch file
to create an environment for building the SDK stuff using CMAKE

%comspec% /k "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvars64.bat"