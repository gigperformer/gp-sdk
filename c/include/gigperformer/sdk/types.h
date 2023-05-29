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

        // For each of these we will have a code representing Add, Delete, Move, Rename
        GPStatus_SongListModifed,
        GPStatus_RackspaceListModified,
        GPStatus_SongPartListModified,
        GPStatus_VariationListModified,
        GPStatus_MetronomeStateChanged,
        GPStatus_SaveRequest
    } GPStatusType;

    /// Specifies which entities are allowed to use injected GPScripts or which scripts are allowed in external API
    typedef enum
    {
        GPScript_Rackspace,
        GPScript_GlobalRackspace,
        GPScript_Gig,
        GPScript_Song,
        GPScript_Scriptlet
    } GPScript_AllowedLocations;

    /// Call this to get the address of a GP_ function
    typedef void *(*TGetGPFunctionType)(void *handle, const char *functionName);

    /// Opaque type needed for GPScript helper functions
    typedef void *GPRuntimeEngine;

    /// Signature of the C implementations for functions exported to GPScript
    typedef void (*TGPScriptExecutableFunctionSignature)(GPRuntimeEngine *vm);

    typedef struct
    {
        const char *functionName;                               ///< Just the name of the function
        const char *args;                                       ///< The args and the optional return type
        const char *returns;                                    ///< optional return type clause
        const char *description;                                ///< For the helper in the script editor
        TGPScriptExecutableFunctionSignature functionToExecute; ///< Pointer to the function implementation
    } ExternalAPI_GPScriptFunctionDefinition;

#ifdef __cplusplus
}
#endif
