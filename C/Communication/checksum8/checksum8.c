#include <stddef.h>

#include "checksum8.h"

checksum8_status_t checksum8_calculate(
    const uint8_t * const data,
    uint32_t length,
    uint8_t * const out_checksum)
{
    uint32_t index = 0U;
    uint8_t checksum = 0U;

    if ((NULL == data) || (NULL == out_checksum))
    {
        return CHECKSUM8_STATUS_INVALID_ARGUMENT;
    }

    for (index = 0U; index < length; ++index)
    {
        checksum = (uint8_t)(checksum + data[index]);
    }

    *out_checksum = checksum;

    return CHECKSUM8_STATUS_SUCCESS;
}