#ifndef BIT_EXTRACT_H
#define BIT_EXTRACT_H

#include <stdint.h>

/**
 * @brief Status returned by the bit extract module.
 */
typedef enum
{
    BIT_EXTRACT_STATUS_SUCCESS = 0U,
    BIT_EXTRACT_STATUS_INVALID_ARGUMENT
} bit_extract_status_t;

/**
 * @brief Extract a bit field from a 32-bit unsigned value.
 *
 * Extracts @p width bits starting at @p position and places the
 * extracted field in the least significant bits of the result.
 *
 * @param[in] value Value containing the bit field.
 * @param[in] position Starting bit position, where bit 0 is the
 *                     least significant bit.
 * @param[in] width Number of bits to extract.
 * @param[out] result Pointer to store the extracted bit field.
 *
 * @retval BIT_EXTRACT_STATUS_SUCCESS
 *         Bit field extracted successfully.
 *
 * @retval BIT_EXTRACT_STATUS_INVALID_ARGUMENT
 *         Result pointer is NULL, position is outside the 32-bit
 *         value, width is zero, or the requested bit field exceeds
 *         the 32-bit value.
 */
bit_extract_status_t bit_extract(
    uint32_t value,
    uint8_t position,
    uint8_t width,
    uint32_t * const result);

#endif