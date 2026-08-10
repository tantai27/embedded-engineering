#ifndef RING_BUFFER_H
#define RING_BUFFER_H

#include <stdint.h>

/**
 * @brief Status returned by the ring_buffer module.
 */
typedef enum
{
    RING_BUFFER_STATUS_SUCCESS = 0U,
    RING_BUFFER_STATUS_FULL,
    RING_BUFFER_STATUS_EMPTY,
    RING_BUFFER_STATUS_INVALID_ARGUMENT
} ring_buffer_status_t;

/**
 * @brief Ring buffer control structure.
 *
 * Stores the buffer memory and the current read/write state.
 */
typedef struct
{
    uint8_t *buffer;
    uint32_t capacity;
    uint32_t read_index;
    uint32_t write_index;
    uint32_t count;
} ring_buffer_t;

/**
 * @brief Initialize a ring buffer.
 *
 * @param[out] rb Pointer to the ring buffer control structure.
 * @param[out] buffer Pointer to the storage memory.
 * @param[in] capacity Number of elements available in the buffer.
 *
 * @retval RING_BUFFER_STATUS_SUCCESS
 *         Initialization completed successfully.
 *
 * @retval RING_BUFFER_STATUS_INVALID_ARGUMENT
 *         Invalid pointer or zero capacity.
 */
ring_buffer_status_t ring_buffer_init(ring_buffer_t * const rb,
                                      uint8_t * const buffer,
                                      uint32_t capacity);

/**
 * @brief Push one byte into the ring buffer.
 *
 * @param[in,out] rb Pointer to the ring buffer.
 * @param[in] data Byte to store.
 *
 * @retval RING_BUFFER_STATUS_SUCCESS
 *         Data was stored successfully.
 *
 * @retval RING_BUFFER_STATUS_FULL
 *         Ring buffer is already full.
 *
 * @retval RING_BUFFER_STATUS_INVALID_ARGUMENT
 *         Invalid ring buffer pointer.
 */
ring_buffer_status_t ring_buffer_push(ring_buffer_t * const rb,
                                      uint8_t data);

/**
 * @brief Pop one byte from the ring buffer.
 *
 * @param[in,out] rb Pointer to the ring buffer.
 * @param[out] data Pointer to store the retrieved byte.
 *
 * @retval RING_BUFFER_STATUS_SUCCESS
 *         Data was retrieved successfully.
 *
 * @retval RING_BUFFER_STATUS_EMPTY
 *         Ring buffer contains no data.
 *
 * @retval RING_BUFFER_STATUS_INVALID_ARGUMENT
 *         Invalid pointer.
 */
ring_buffer_status_t ring_buffer_pop(ring_buffer_t * const rb,
                                     uint8_t * const data);

#endif