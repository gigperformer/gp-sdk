#include <interfaces/C/macros.h>
#include <interfaces/C/exports.h>
#include <interfaces/C/imports.h>
#include <stdio.h>


LibraryHandle Handle; // Unique identifier for this library. Must be passed when calling into GP

// These are functions that can be called FROM Gig Performer 
// Developer must implement these functions using the signatures in exports.h


// Get information about this library so that GP user can decide whether it should be loaded
EXPORTED void GPQueryLibrary(char* xmlInfoBuffer, int bufferLength)
{
    char buffer[] = 
   "<Library> \
    <Product Name=\"Hello GP - C\" Version=\"1.0\" BuildDate=\"12/1/2019\"></Product> \
    <Description>This product does blah blah blah</Description> \
    <ImagePath>/Path/To/ImageFile/foo.jpg</ImagePath> \
    </Library>"; 

    snprintf(xmlInfoBuffer, bufferLength, "%s", buffer);

}


// If this is newer than the version expected by GP then a crash may occur. Do NOT change this information.

EXPORTED int GPGetSDKVersion()
{
   return GPSDK_VERSION;
}


// You MUST implement this function call AND call the InitializeImportedFunctions function 
EXPORTED  void GPRegister(TGetGPFunctionType getGPFunctionAddress, LibraryHandle handle)
{
   Handle = handle;
   InitializeImportedFunctions(handle, getGPFunctionAddress);
   GP_RegisterCallback(handle, "OnSongChanged");
   GP_ConsoleLog(Handle, "GP_Test-Lib Loaded.");
    
   
}


// The rest of these are optional but make sure that any function you register with GP_RegisterCallback
// are actually implemented or you will get an immediate crash

EXPORTED void OnSongChanged(int oldIndex, int newIndex)
{
    char str[255];
    sprintf(str, "Song changed from: %d, to: %d", oldIndex, newIndex);
    
    GP_ConsoleLog(Handle, str);
}

