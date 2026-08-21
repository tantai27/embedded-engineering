#ifndef CRC16_H
#define CRC16_H

#include <stdint.h>

/**
 * @brief Status returned by the crc16 module.
 */
typedef enum
{
    CRC16_STATUS_SUCCESS = 0U,
    CRC16_STATUS_INVALID_ARGUMENT
} crc16_status_t;

/**
 * @brief Calculate CRC-16/IBM checksum for a byte array.
 *
 * Processes the input data byte by byte and bit by bit using the
 * CRC-16/IBM algorithm.
 *
 * CRC-16/IBM parameters:
 * - Polynomial: 0x8005
 * - Initial value: 0x0000
 * - Input reflection: Enabled
 * - Output reflection: Enabled
 * - Final XOR value: 0x0000
 *
 * @param[in] data Pointer to the input byte array.
 * @param[in] length Number of bytes to process.
 * @param[out] out_crc Pointer to store the calculated CRC value.
 *
 * @retval CRC16_STATUS_SUCCESS
 *         CRC calculation completed successfully.
 *
 * @retval CRC16_STATUS_INVALID_ARGUMENT
 *         One or more input arguments are invalid.
 */
crc16_status_t crc16_calculate(const uint8_t * const data,
                               uint32_t length,
                               uint16_t * const out_crc);

#endif