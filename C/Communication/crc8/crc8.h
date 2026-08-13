#ifndef CRC8_H
#define CRC8_H

#include <stdint.h>

/**
 * @brief Status returned by the CRC-8 module.
 */
typedef enum
{
    CRC8_STATUS_SUCCESS = 0U,
    CRC8_STATUS_INVALID_ARGUMENT
} crc8_status_t;

/**
 * @brief Calculate CRC-8 for a byte array.
 *
 * Uses the CRC-8/ITU algorithm with polynomial 0x07,
 * initial value 0x00, no input/output reflection,
 * and XOR output value 0x00.
 *
 * @param[in] data Pointer to the input byte array.
 * @param[in] length Number of bytes in the input array.
 * @param[out] out_crc Pointer to store the calculated CRC.
 *
 * @retval CRC8_STATUS_SUCCESS
 *         CRC calculation completed successfully.
 *
 * @retval CRC8_STATUS_INVALID_ARGUMENT
 *         Invalid input pointer.
 */
crc8_status_t crc8_calculate(const uint8_t * const data,
                             uint32_t length,
                             uint8_t * const out_crc);

#endif