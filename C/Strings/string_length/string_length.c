#include <stddef.h>
#include <stdint.h>

#include "string_length.h"

str_status_t string_length(const char * const str,
                                         uint32_t * const out_length)
{
    const char *ptr = NULL;
    uint32_t length_counter = 0U;

    if ((NULL == str) || (NULL == out_length))
    {
        return STR_STATUS_ERR_PARAM;
    }

    ptr = str;

    while ('\0' != *ptr)
    {
        if (UINT32_MAX == length_counter)
        {
            return STR_STATUS_ERR_OVERFLOW;
        }

        ++length_counter;
        ++ptr;
    }

    *out_length = length_counter;

    return STR_STATUS_OK;
}