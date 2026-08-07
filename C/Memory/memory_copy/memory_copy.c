#include <stddef.h>
#include <stdint.h>

#include "memory_copy.h"

mem_status_t memory_copy(void * const dest,
                         const void * const src,
                         size_t length)
{
    uint8_t *dest_ptr = NULL;
    const uint8_t *src_ptr = NULL;

    if ((NULL == dest) || (NULL == src))
    {
        return MEM_STATUS_INVALID_ARGUMENT;
    }

    dest_ptr = (uint8_t *)dest;
    src_ptr = (const uint8_t *)src;

    if ((dest_ptr > src_ptr) &&
        (dest_ptr < (src_ptr + length)))
    {
        while (0U != length)
        {
            --length;
            dest_ptr[length] = src_ptr[length];
        }
    }
    else
    {
        for (size_t index = 0U;
             index < length;
             ++index)
        {
            dest_ptr[index] = src_ptr[index];
        }
    }

    return MEM_STATUS_SUCCESS;
}