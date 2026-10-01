#ifndef INSERTION_SORT_H
#define INSERTION_SORT_H

#include <stdint.h>

/**
 * @brief Status returned by the insertion sort module.
 */
typedef enum
{
    INSERTION_SORT_STATUS_SUCCESS = 0U,
    INSERTION_SORT_STATUS_INVALID_ARGUMENT
} insertion_sort_status_t;

/**
 * @brief Sort an array of 32-bit unsigned integers in ascending order.
 *
 * Uses the Insertion Sort algorithm. Each element is inserted into its
 * correct position within the already sorted portion of the array.
 *
 * @param[in,out] data Pointer to the array to be sorted.
 * @param[in] length Number of elements in the array.
 *
 * @retval INSERTION_SORT_STATUS_SUCCESS
 *         Sorting completed successfully, including when length is zero.
 *
 * @retval INSERTION_SORT_STATUS_INVALID_ARGUMENT
 *         The data pointer is NULL while length is non-zero.
 */
insertion_sort_status_t insertion_sort(
    uint32_t * const data,
    uint32_t length);

#endif