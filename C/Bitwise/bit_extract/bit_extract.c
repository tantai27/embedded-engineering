#include <stddef.h>

#include "bit_extract.h"

#define BIT_EXTRACT_UINT32_WIDTH    (32U)

bit_extract_status_t bit_extract(
    uint32_t value,
    uint8_t position,
    uint8_t width,
    uint32_t * const result)
{
    uint32_t mask;

    if ((NULL == result) ||
        (position >= BIT_EXTRACT_UINT32_WIDTH) ||
        (0U == width) ||
        ((uint32_t)position + (uint32_t)width >
         BIT_EXTRACT_UINT32_WIDTH))
    {
        return BIT_EXTRACT_STATUS_INVALID_ARGUMENT;
    }

    if (BIT_EXTRACT_UINT32_WIDTH == width)
    {
        mask = UINT32_MAX;
    }
    else
    {
        mask = (1UL << width) - 1UL;
    }

    *result = (value >> position) & mask;

    return BIT_EXTRACT_STATUS_SUCCESS;
}