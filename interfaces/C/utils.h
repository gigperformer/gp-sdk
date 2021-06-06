#pragma once

#include <stdint.h>

// Convert a string to hex bytes - mostly intended for sysex messages
// It is your responsibility to make sure that the space to which target points
// is large enough (generally should be half the size of the ascii length of the string)
#ifdef __cplusplus
extern "C"
{
#endif

extern void hex2bin(const char* src, uint8_t* target);

#ifdef __cplusplus
}
#endif
