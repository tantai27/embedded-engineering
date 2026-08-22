#ifndef QUEUE_H
#define QUEUE_H

#include <stdint.h>

/**
 * @brief Status returned by the queue module.
 */
typedef enum
{
    QUEUE_STATUS_SUCCESS = 0U,
    QUEUE_STATUS_FULL,
    QUEUE_STATUS_EMPTY,
    QUEUE_STATUS_INVALID_ARGUMENT
} queue_status_t;

/**
 * @brief Fixed-size FIFO queue control structure.
 */
typedef struct
{
    uint32_t *buffer;
    uint32_t capacity;
    uint32_t head;
    uint32_t tail;
    uint32_t count;
} queue_t;

/**
 * @brief Initialize a fixed-size queue.
 *
 * @param[out] queue Pointer to the queue control structure.
 * @param[out] buffer Pointer to externally allocated storage.
 * @param[in] capacity Maximum number of elements.
 *
 * @retval QUEUE_STATUS_SUCCESS
 *         Queue initialized successfully.
 *
 * @retval QUEUE_STATUS_INVALID_ARGUMENT
 *         One or more input arguments are invalid.
 */
queue_status_t queue_init(queue_t * const queue,
                           uint32_t * const buffer,
                           uint32_t capacity);

/**
 * @brief Add an element to the queue.
 *
 * @param[in,out] queue Pointer to the queue.
 * @param[in] data Element to add.
 *
 * @retval QUEUE_STATUS_SUCCESS
 *         Element added successfully.
 *
 * @retval QUEUE_STATUS_FULL
 *         Queue is full.
 *
 * @retval QUEUE_STATUS_INVALID_ARGUMENT
 *         Queue pointer is invalid.
 */
queue_status_t queue_push(queue_t * const queue,
                           uint32_t data);

/**
 * @brief Remove the oldest element from the queue.
 *
 * @param[in,out] queue Pointer to the queue.
 * @param[out] data Pointer to store the removed element.
 *
 * @retval QUEUE_STATUS_SUCCESS
 *         Element removed successfully.
 *
 * @retval QUEUE_STATUS_EMPTY
 *         Queue is empty.
 *
 * @retval QUEUE_STATUS_INVALID_ARGUMENT
 *         One or more input arguments are invalid.
 */
queue_status_t queue_pop(queue_t * const queue,
                          uint32_t * const data);

#endif