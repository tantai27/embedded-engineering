#include "bit_rotate.h"

#define BIT_ROTATE_UINT8_WIDTH    (8U)

uint8_t bit_rotate_left(
    uint8_t value,
    uint8_t shift)
{
    uint8_t normalized_shift;

    normalized_shift = shift % BIT_ROTATE_UINT8_WIDTH;

    if (0U == normalized_shift)
    {
        return value;
    }

    return (uint8_t)((uint8_t)(value << normalized_shift) |
                     (uint8_t)(value >>
                         (BIT_ROTATE_UINT8_WIDTH - normalized_shift)));
}

uint8_t bit_rotate_right(
    uint8_t value,
    uint8_t shift)
{
    uint8_t normalized_shift;

    normalized_shift = shift % BIT_ROTATE_UINT8_WIDTH;

    if (0U == normalized_shift)
    {
        return value;
    }

    return (uint8_t)((uint8_t)(value >> normalized_shift) |
                     (uint8_t)(value <<
                         (BIT_ROTATE_UINT8_WIDTH - normalized_shift)));
}