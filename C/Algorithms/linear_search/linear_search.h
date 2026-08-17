#ifndef LINEAR_SEARCH_H
#define LINEAR_SEARCH_H

#include <stdint.h>

/**
 * @brief Status returned by the linear_search module.
 */
typedef enum
{
    LINEAR_SEARCH_STATUS_SUCCESS = 0U,
    LINEAR_SEARCH_STATUS_NOT_FOUND,
    LINEAR_SEARCH_STATUS_INVALID_ARGUMENT
} linear_search_status_t;

/**
 * @brief Search for a value in an array using Linear Search.
 *
 * Searches the input array sequentially from the first element to the last
 * element until the target value is found or all elements have been checked.
 *
 * @param[in] arr Pointer to the input array.
 * @param[in] size Number of elements in the array.
 * @param[in] target Value to search for.
 * @param[out] out_index Pointer to store the index of the first match.
 *
 * @retval LINEAR_SEARCH_STATUS_SUCCESS
 *         Target found.
 *
 * @retval LINEAR_SEARCH_STATUS_NOT_FOUND
 *         Target does not exist in the array.
 *
 * @retval LINEAR_SEARCH_STATUS_INVALID_ARGUMENT
 *         Invalid input pointer or zero array size.
 */
linear_search_status_t linear_search(const uint32_t * const arr,
                                     uint32_t size,
                                     uint32_t target,
                                     uint32_t * const out_index);

#endif