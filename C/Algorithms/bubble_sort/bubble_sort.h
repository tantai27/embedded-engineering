#ifndef BUBBLE_SORT_H
#define BUBBLE_SORT_H

#include <stdint.h>

/**
 * @brief Status returned by the bubble sort module.
 */
typedef enum
{
    BUBBLE_SORT_STATUS_SUCCESS = 0U,
    BUBBLE_SORT_STATUS_INVALID_ARGUMENT
} bubble_sort_status_t;

/**
 * @brief Sort an array of 32-bit unsigned integers in ascending order.
 *
 * Uses bubble sort with an early-exit optimization when no swaps
 * are performed during a complete pass.
 *
 * @param[in,out] data Pointer to the array to be sorted.
 * @param[in] length Number of elements in the array.
 *
 * @retval BUBBLE_SORT_STATUS_SUCCESS
 *         The array was sorted successfully, including when length is zero.
 *
 * @retval BUBBLE_SORT_STATUS_INVALID_ARGUMENT
 *         The data pointer is NULL while length is non-zero.
 */
bubble_sort_status_t bubble_sort(
    uint32_t * const data,
    uint32_t length);

#endif