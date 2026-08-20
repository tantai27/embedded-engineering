#ifndef STRING_COPY_H
#define STRING_COPY_H

#include <stdint.h>

/**
 * @brief Status returned by the string_copy module.
 */
typedef enum
{
    STRING_COPY_STATUS_SUCCESS = 0U,
    STRING_COPY_STATUS_INVALID_ARGUMENT,
    STRING_COPY_STATUS_BUFFER_TOO_SMALL
} string_copy_status_t;

/**
 * @brief Safely copy a null-terminated string to a destination buffer.
 *
 * Copies the source string including the null terminator into the destination
 * buffer. The function does not write beyond the provided destination size.
 *
 * @param[out] dest Pointer to the destination buffer.
 * @param[in] dest_size Size of the destination buffer in bytes.
 * @param[in] src Pointer to the source null-terminated string.
 *
 * @retval STRING_COPY_STATUS_SUCCESS
 *         String copied successfully.
 *
 * @retval STRING_COPY_STATUS_INVALID_ARGUMENT
 *         One or more input arguments are invalid.
 *
 * @retval STRING_COPY_STATUS_BUFFER_TOO_SMALL
 *         Destination buffer is not large enough to contain the source string
 *         including the null terminator.
 */
string_copy_status_t string_copy(char * const dest,
                                 uint32_t dest_size,
                                 const char * const src);

#endif