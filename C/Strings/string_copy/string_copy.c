#include <stddef.h>

#include "string_copy.h"

string_copy_status_t string_copy(char * const dest,
                                 uint32_t dest_size,
                                 const char * const src)
{
    uint32_t index = 0U;

    if ((NULL == dest) || (NULL == src) || (0U == dest_size))
    {
        return STRING_COPY_STATUS_INVALID_ARGUMENT;
    }

    while (('\0' != src[index]) && (index < (dest_size - 1U)))
    {
        dest[index] = src[index];
        ++index;
    }

    if ('\0' != src[index])
    {
        return STRING_COPY_STATUS_BUFFER_TOO_SMALL;
    }

    dest[index] = '\0';

    return STRING_COPY_STATUS_SUCCESS;
}