#include <stddef.h>

#include "parity8.h"

parity8_status_t parity8_calculate(
    uint8_t data,
    parity8_type_t type,
    uint8_t * const parity)
{
    uint8_t bit_parity;

    if ((NULL == parity) ||
        ((PARITY8_EVEN != type) &&
         (PARITY8_ODD != type)))
    {
        return PARITY8_STATUS_INVALID_ARGUMENT;
    }

    bit_parity = 0U;

    while (0U != data)
    {
        bit_parity ^= (uint8_t)(data & 1U);
        data >>= 1U;
    }

    if (PARITY8_ODD == type)
    {
        bit_parity ^= 1U;
    }

    *parity = bit_parity;

    return PARITY8_STATUS_SUCCESS;
}