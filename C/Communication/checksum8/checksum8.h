#ifndef CHECKSUM8_H
#define CHECKSUM8_H

#include <stdint.h>

/**
 * @brief Status returned by the checksum8 module.
 */
typedef enum
{
    CHECKSUM8_STATUS_SUCCESS = 0U,
    CHECKSUM8_STATUS_INVALID_ARGUMENT
} checksum8_status_t;

/**
 * @brief Calculate an 8-bit additive checksum.
 *
 * The checksum is calculated by summing all input bytes. The resulting
 * value is truncated to 8 bits.
 *
 * @param[in] data Pointer to the input byte array.
 * @param[in] length Number of bytes to process.
 * @param[out] out_checksum Pointer to store the calculated checksum.
 *
 * @retval CHECKSUM8_STATUS_SUCCESS
 *         Checksum calculation completed successfully.
 *
 * @retval CHECKSUM8_STATUS_INVALID_ARGUMENT
 *         One or more input arguments are invalid.
 */
checksum8_status_t checksum8_calculate(
    const uint8_t * const data,
    uint32_t length,
    uint8_t * const out_checksum);

#endif