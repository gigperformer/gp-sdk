/// \file    utils.h
/// \brief   Helpful functions for C extension implementers

#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif
    /// \brief   Convert a string to hex bytes.
    /// \details mostly intended for SysEx messages.
    /// \param   src
    /// \param   target It is the callers responsibility to make sure that the space to which target points is large
    ///                 enough (generally should be half the size of the ASCII length of the src)
    extern void hex2bin(const char *src, uint8_t *target);

#ifdef __cplusplus
}
#endif
