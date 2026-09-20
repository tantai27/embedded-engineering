#ifndef PARITY8_H
#define PARITY8_H

#include <stdint.h>

/**
 * @brief Status returned by the parity8 module.
 */
typedef enum
{
    PARITY8_STATUS_SUCCESS = 0U,
    PARITY8_STATUS_INVALID_ARGUMENT
} parity8_status_t;

/**
 * @brief Parity mode.
 */
typedef enum
{
    PARITY8_EVEN = 0U,
    PARITY8_ODD
} parity8_type_t;

/**
 * @brief Calculate the parity bit of an 8-bit value.
 *
 * Calculates the parity bit required to make the total number of
 * set bits even or odd.
 *
 * @param[in] data 8-bit input value.
 * @param[in] type Desired parity type.
 * @param[out] parity Pointer to store the calculated parity bit.
 *
 * @retval PARITY8_STATUS_SUCCESS
 *         Parity calculated successfully.
 *
 * @retval PARITY8_STATUS_INVALID_ARGUMENT
 *         The parity pointer is NULL or the parity type is invalid.
 */
parity8_status_t parity8_calculate(
    uint8_t data,
    parity8_type_t type,
    uint8_t * const parity);

#endif