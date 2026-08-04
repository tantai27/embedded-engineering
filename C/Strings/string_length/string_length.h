#ifndef STRING_LENGTH_H
#define STRING_LENGTH_H

#include <stdint.h>

/**
 * @brief Status returned by the string_length module.
 */
typedef enum
{
    STR_STATUS_OK = 0U,
    STR_STATUS_ERR_PARAM,
    STR_STATUS_ERR_OVERFLOW
} str_status_t;

/**
 * @brief Calculate the length of a null-terminated string.
 *
 * Counts the number of characters before the terminating
 * null character ('\0').
 *
 * @param[in] str Pointer to the input string.
 * @param[out] out_length Pointer to store the calculated length.
 *
 * @retval STR_STATUS_OK
 *         Operation completed successfully.
 *
 * @retval STR_STATUS_ERR_PARAM
 *         Invalid input pointer.
 *
 * @retval STR_STATUS_ERR_OVERFLOW
 *         String length exceeds the storage capacity of uint32_t.
 */
str_status_t string_length(const char * const str,
                                         uint32_t * const out_length);

#endif