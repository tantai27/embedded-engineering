#ifndef STRING_COMPARE_H
#define STRING_COMPARE_H

#include <stdint.h>

/**
 * @brief Status returned by the string_compare module.
 */
typedef enum
{
    STRING_COMPARE_STATUS_EQUAL = 0U,
    STRING_COMPARE_STATUS_NOT_EQUAL,
    STRING_COMPARE_STATUS_INVALID_ARGUMENT
} string_compare_status_t;

/**
 * @brief Compare two null-terminated strings.
 *
 * Compares two strings character by character until a difference is found
 * or both strings reach the null terminator.
 *
 * @param[in] lhs Pointer to the first null-terminated string.
 * @param[in] rhs Pointer to the second null-terminated string.
 *
 * @retval STRING_COMPARE_STATUS_EQUAL
 *         Both strings contain identical characters.
 *
 * @retval STRING_COMPARE_STATUS_NOT_EQUAL
 *         The strings contain different characters.
 *
 * @retval STRING_COMPARE_STATUS_INVALID_ARGUMENT
 *         One or more input pointers are invalid.
 */
string_compare_status_t string_compare(const char * const lhs,
                                       const char * const rhs);

#endif