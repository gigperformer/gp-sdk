/// \file    types.h
/// \brief   Definitions of C types

#pragma once

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

    typedef void *LibraryHandle;

    /// For use with OnModeChanged()
    enum GP_Mode
    {
        GP_FrontBackMode = 0,
        GP_SetlistMode = 1,
    };

    /// Options for the OnGigStatusChanged callback
    typedef enum
    {
        GPStatus_GigFinishedLoading,
        GPStatus_GigStartedLoading,
        GPStatus_GigFailedLoading,
    } GPStatusType;

    /// Call this to get the address of a GP_ function
    typedef void *(*TGetGPFunctionType)(void *handle, const char *functionName);

#ifdef __cplusplus
}
#endif
