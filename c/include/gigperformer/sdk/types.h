/// \file    types.h
/// \brief   Definitions of C types

#pragma once

#include <stdbool.h>
#include <stdint.h>

typedef void *LibraryHandle;

/// For use with OnModeChanged()
enum GP_Mode
{
    GP_FrontBackMode = 0,
    GP_SetlistMode = 1,
};

enum ExternalAPI_GPStatus
{
    GPStatus_GigFinishedLoading,
    GPStatus_GigStartedLoading,
    GPStatus_GigFailedLoading,
};

/// Call this to get the address of a GP_ function
typedef void *(*TGetGPFunctionType)(void *handle, const char *functionName);
