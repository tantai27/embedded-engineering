#ifndef BIT_ROTATE_H
#define BIT_ROTATE_H

#include <stdint.h>

/**
 * @brief Rotate an 8-bit value to the left.
 *
 * Bits shifted out from the most significant side are inserted
 * back into the least significant side.
 *
 * The shift value is normalized to the 8-bit width.
 *
 * @param[in] value Value to rotate.
 * @param[in] shift Number of bit positions to rotate.
 *
 * @return Rotated 8-bit value.
 */
uint8_t bit_rotate_left(
    uint8_t value,
    uint8_t shift);

/**
 * @brief Rotate an 8-bit value to the right.
 *
 * Bits shifted out from the least significant side are inserted
 * back into the most significant side.
 *
 * The shift value is normalized to the 8-bit width.
 *
 * @param[in] value Value to rotate.
 * @param[in] shift Number of bit positions to rotate.
 *
 * @return Rotated 8-bit value.
 */
uint8_t bit_rotate_right(
    uint8_t value,
    uint8_t shift);

#endif