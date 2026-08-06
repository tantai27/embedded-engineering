#ifndef BINARY_SEARCH_H
#define BINARY_SEARCH_H

#include <stdint.h>

/**
 * @brief Status returned by the binary_search module.
 */
typedef enum
{
    SEARCH_STATUS_SUCCESS = 0U,
    SEARCH_STATUS_NOT_FOUND,
    SEARCH_STATUS_INVALID_ARGUMENT
} search_status_t;

/**
 * @brief Search a value in a sorted array using Binary Search.
 *
 * Searches for the specified target value in an array sorted
 * in ascending order.
 *
 * @param[in] arr Pointer to the input array.
 * @param[in] size Number of elements in the array.
 * @param[in] target Value to search for.
 * @param[out] out_index Pointer to store the index if found.
 *
 * @retval SEARCH_STATUS_SUCCESS
 *         Target found.
 *
 * @retval SEARCH_STATUS_NOT_FOUND
 *         Target does not exist in the array.
 *
 * @retval SEARCH_STATUS_INVALID_ARGUMENT
 *         Invalid input pointer or zero array size.
 */
search_status_t binary_search(const uint32_t * const arr,
                              uint32_t size,
                              uint32_t target,
                              uint32_t * const out_index);

#endif