#pragma once



// We need to check compatibility with GP --- certain changes can cause breakage
#define GPSDK_VERSION 44


// GigStatusChanged options for the OnGigStatusChanged callback
typedef enum
{
    GPStatus_GigFinishedLoading,
    GPStatus_GigStartedLoading,
    GPStatus_GigFailedLoading,
} GPStatusType; 

// Specify which entities are allowed to use injected GP Scripts or which scripts are allowed in external API
typedef enum
{
   GPScript_Rackspace,
   GPScript_GlobalRackspace,
   GPScript_Gig,
   GPScript_Song,
   GPScript_Scriptlet
} GPScript_AllowedLocations;


typedef
   void*
      GPRuntimeEngine; // Opague type needed for GPScript helper functions

typedef
   void (*TGPScriptExecutableFunctionSignature)(GPRuntimeEngine* vm);      


typedef
   struct
      {
         const char* functionName; // Just the name of the function
         const char* args; // The args and the optional return type
         const char* returns; // optional return type clause
         const char* description; // For the helper in the script editor
         TGPScriptExecutableFunctionSignature functionToExecute;
      }
      ExternaAPI_GPScriptFunctionDefinition;



#include <inttypes.h>
//#include <cstddef>
#include <stdbool.h>

#ifdef __cplusplus
namespace DeskewGP
{
#endif

   typedef
      void*
         LibraryHandle;

   typedef 
      void* (*TGetGPFunctionType)(void* handle, const char* functionName); // Call this to get the address of a GP_ function         

#ifdef __cplusplus
}   
#endif