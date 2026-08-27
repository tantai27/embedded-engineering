#include <stddef.h>

#include "buffer_copy.h"

buffer_copy_status_t buffer_copy(
    uint8_t * const destination,
    const uint8_t * const source,
    uint32_t length)
{
    uint32_t index = 0U;

    if (0U == length)
    {
        return BUFFER_COPY_STATUS_SUCCESS;
    }

    if ((NULL == destination) || (NULL == source))
    {
        return BUFFER_COPY_STATUS_INVALID_ARGUMENT;
    }

    if ((destination < source) &&
        ((destination + length) > source))
    {
        return BUFFER_COPY_STATUS_OVERLAP;
    }

    if ((source < destination) &&
        ((source + length) > destination))
    {
        return BUFFER_COPY_STATUS_OVERLAP;
    }

    for (index = 0U; index < length; ++index)
    {
        destination[index] = source[index];
    }

    return BUFFER_COPY_STATUS_SUCCESS;
}