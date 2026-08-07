#ifndef MEMORY_COPY_H
#define MEMORY_COPY_H

#include <stddef.h>
#include <stdint.h>

/**
 * @brief Status returned by the memory_copy module.
 */
typedef enum
{
    MEM_STATUS_SUCCESS = 0U,
    MEM_STATUS_INVALID_ARGUMENT
} mem_status_t;

/**
 * @brief Copy memory from source to destination.
 *
 * Copies the specified number of bytes from the source buffer
 * to the destination buffer.
 *
 * The implementation safely handles overlapping memory regions.
 *
 * @param[out] dest Pointer to the destination buffer.
 * @param[in] src Pointer to the source buffer.
 * @param[in] length Number of bytes to copy.
 *
 * @retval MEM_STATUS_SUCCESS
 *         Copy completed successfully.
 *
 * @retval MEM_STATUS_INVALID_ARGUMENT
 *         Invalid input pointer.
 */
mem_status_t memory_copy(void * const dest,
                         const void * const src,
                         size_t length);

#endif