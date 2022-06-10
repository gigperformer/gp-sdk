#include "gigperformer/sdk/utils.h"

#include <assert.h>
#include <stdbool.h>
#define then

#ifdef __cplusplus
extern "C"
{
#endif

    static uint8_t hexchar2int(char input)
    {
        // Yes, I know, you could create an array of 256 bytes and just convert by
        // indexing through the array
        uint8_t result = 0;

        if (input >= 'A' && input <= 'F')
            then result = input - 'A' + 10;
        else if (input >= '0' && input <= '9')
            then result = input - '0';
        else if (input >= 'a' && input <= 'f')
            then result = input - 'a' + 10;
        // else assert(false);   // Just ignore anything else

        return result;
    }

    // This function assumes src to be a zero terminated sanitized string with
    // an even number of [0-9a-f] characters, and target to be sufficiently large
    void hex2bin(const char *src, uint8_t *target)
    {
        while (*src && src[1])
        {
            *(target++) = hexchar2int(*src) * 16 + hexchar2int(src[1]);
            src += 2;
        }
    }

#ifdef __cplusplus
}
#endif
