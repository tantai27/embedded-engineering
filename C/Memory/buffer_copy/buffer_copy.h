#ifndef BUFFER_COPY_H
#define BUFFER_COPY_H

#include <stdint.h>

/**
 * @brief Status returned by the buffer copy module.
 */
typedef enum
{
    BUFFER_COPY_STATUS_SUCCESS = 0U,
    BUFFER_COPY_STATUS_INVALID_ARGUMENT,
    BUFFER_COPY_STATUS_OVERLAP
} buffer_copy_status_t;

/**
 * @brief Copy a block of bytes from source to destination.
 *
 * The source and destination buffers must not overlap.
 *
 * @param[out] destination Destination buffer.
 * @param[in] source Source buffer.
 * @param[in] length Number of bytes to copy.
 *
 * @retval BUFFER_COPY_STATUS_SUCCESS
 *         Buffer copied successfully.
 *
 * @retval BUFFER_COPY_STATUS_INVALID_ARGUMENT
 *         One or more pointers are invalid.
 *
 * @retval BUFFER_COPY_STATUS_OVERLAP
 *         Source and destination buffers overlap.
 */
buffer_copy_status_t buffer_copy(
    uint8_t * const destination,
    const uint8_t * const source,
    uint32_t length);

#endif