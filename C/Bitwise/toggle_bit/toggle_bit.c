#include <stddef.h>

#include "toggle_bit.h"

#define UINT32_BIT_WIDTH    (32U)

status_t toggle_bit(volatile uint32_t * const reg,
                    uint8_t pos)
{
    if ((NULL == reg) || (pos >= UINT32_BIT_WIDTH))
    {
        return STATUS_INVALID_ARGUMENT;
    }

    *reg ^= (1UL << pos);

    return STATUS_SUCCESS;
}