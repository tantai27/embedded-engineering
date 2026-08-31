#ifndef STRING_REVERSE_H
#define STRING_REVERSE_H

#include <stdint.h>

/**
 * @brief Status returned by the string reverse module.
 */
typedef enum
{
    STRING_REVERSE_STATUS_SUCCESS = 0U,
    STRING_REVERSE_STATUS_INVALID_ARGUMENT
} string_reverse_status_t;

/**
 * @brief Reverse a null-terminated string in place.
 *
 * @param[in,out] string Pointer to the string buffer.
 *
 * @retval STRING_REVERSE_STATUS_SUCCESS
 *         String reversed successfully.
 *
 * @retval STRING_REVERSE_STATUS_INVALID_ARGUMENT
 *         String pointer is NULL.
 */
string_reverse_status_t string_reverse(
    char * const string);

#endif