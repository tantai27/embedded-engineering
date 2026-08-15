#ifndef MEMORY_COMPARE_H
#define MEMORY_COMPARE_H

#include <stdint.h>

/**
 * @brief Status returned by the memory_compare module.
 */
typedef enum
{
    MEMORY_COMPARE_STATUS_EQUAL = 0U,
    MEMORY_COMPARE_STATUS_NOT_EQUAL,
    MEMORY_COMPARE_STATUS_INVALID_ARGUMENT
} memory_compare_status_t;

/**
 * @brief Compare two memory regions byte by byte.
 *
 * Compares two memory regions for equality.
 *
 * @param[in] lhs Pointer to the first memory region.
 * @param[in] rhs Pointer to the second memory region.
 * @param[in] size Number of bytes to compare.
 *
 * @retval MEMORY_COMPARE_STATUS_EQUAL
 *         Both memory regions contain identical data.
 *
 * @retval MEMORY_COMPARE_STATUS_NOT_EQUAL
 *         The memory regions contain different data.
 *
 * @retval MEMORY_COMPARE_STATUS_INVALID_ARGUMENT
 *         One or more input arguments are invalid.
 */
memory_compare_status_t memory_compare(const void * const lhs,
                                       const void * const rhs,
                                       uint32_t size);

#endif