#pragma once

#include <inttypes.h>
//#include <cstddef>
#include <stdbool.h>

typedef void *LibraryHandle;

typedef void *(*TGetGPFunctionType)(void *handle,
                                    const char *functionName); // Call this to get the address of a GP_ function
