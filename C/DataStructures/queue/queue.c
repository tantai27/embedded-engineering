#include <stddef.h>

#include "queue.h"

queue_status_t queue_init(queue_t * const queue,
                           uint32_t * const buffer,
                           uint32_t capacity)
{
    if ((NULL == queue) || (NULL == buffer) || (0U == capacity))
    {
        return QUEUE_STATUS_INVALID_ARGUMENT;
    }

    queue->buffer = buffer;
    queue->capacity = capacity;
    queue->head = 0U;
    queue->tail = 0U;
    queue->count = 0U;

    return QUEUE_STATUS_SUCCESS;
}

queue_status_t queue_push(queue_t * const queue,
                           uint32_t data)
{
    if (NULL == queue)
    {
        return QUEUE_STATUS_INVALID_ARGUMENT;
    }

    if (queue->count >= queue->capacity)
    {
        return QUEUE_STATUS_FULL;
    }

    queue->buffer[queue->tail] = data;

    ++queue->tail;

    if (queue->tail >= queue->capacity)
    {
        queue->tail = 0U;
    }

    ++queue->count;

    return QUEUE_STATUS_SUCCESS;
}

queue_status_t queue_pop(queue_t * const queue,
                          uint32_t * const data)
{
    if ((NULL == queue) || (NULL == data))
    {
        return QUEUE_STATUS_INVALID_ARGUMENT;
    }

    if (0U == queue->count)
    {
        return QUEUE_STATUS_EMPTY;
    }

    *data = queue->buffer[queue->head];

    ++queue->head;

    if (queue->head >= queue->capacity)
    {
        queue->head = 0U;
    }

    --queue->count;

    return QUEUE_STATUS_SUCCESS;
}