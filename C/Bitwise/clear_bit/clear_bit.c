#include <stddef.h>

#include "clear_bit.h"

#define UINT32_BIT_WIDTH    (32U)

status_t clear_bit(volatile uint32_t * const reg,
                   uint8_t pos)
{
    if ((NULL == reg) || (pos >= UINT32_BIT_WIDTH))
    {
        return STATUS_INVALID_ARGUMENT;
    }

    *reg &= ~(1UL << pos);

    return STATUS_SUCCESS;
}