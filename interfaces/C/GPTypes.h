#pragma once


enum ExternalAPI_GPStatus
{
   GPStatus_GigFinishedLoading,
   GPStatus_GigStartedLoading,
   GPStatus_GigFailedLoading,
};


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