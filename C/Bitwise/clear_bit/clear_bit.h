#ifndef CLEAR_BIT_H
#define CLEAR_BIT_H

#include <stdint.h>

typedef enum
{
    STATUS_SUCCESS = 0U,
    STATUS_INVALID_ARGUMENT
} status_t;

/**
 * @brief Clear a bit in a 32-bit register.
 *
 * Clears the bit at the specified position.
 *
 * @param[in,out] reg Pointer to the target register.
 * @param[in] pos Bit position in the range [0, 31].
 *
 * @retval STATUS_SUCCESS          Operation completed successfully.
 * @retval STATUS_INVALID_ARGUMENT Invalid pointer or bit position.
 */
status_t clear_bit(volatile uint32_t * const reg,
                   uint8_t pos);

#endif