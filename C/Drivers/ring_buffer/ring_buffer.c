#include <stddef.h>

#include "ring_buffer.h"

ring_buffer_status_t ring_buffer_init(ring_buffer_t * const rb,
                                      uint8_t * const buffer,
                                      uint32_t capacity)
{
    if ((NULL == rb) || (NULL == buffer) || (0U == capacity))
    {
        return RING_BUFFER_STATUS_INVALID_ARGUMENT;
    }

    rb->buffer = buffer;
    rb->capacity = capacity;
    rb->read_index = 0U;
    rb->write_index = 0U;
    rb->count = 0U;

    return RING_BUFFER_STATUS_SUCCESS;
}

ring_buffer_status_t ring_buffer_push(ring_buffer_t * const rb,
                                      uint8_t data)
{
    if (NULL == rb)
    {
        return RING_BUFFER_STATUS_INVALID_ARGUMENT;
    }

    if (rb->count >= rb->capacity)
    {
        return RING_BUFFER_STATUS_FULL;
    }

    rb->buffer[rb->write_index] = data;

    ++rb->write_index;

    if (rb->write_index >= rb->capacity)
    {
        rb->write_index = 0U;
    }

    ++rb->count;

    return RING_BUFFER_STATUS_SUCCESS;
}

ring_buffer_status_t ring_buffer_pop(ring_buffer_t * const rb,
                                     uint8_t * const data)
{
    if ((NULL == rb) || (NULL == data))
    {
        return RING_BUFFER_STATUS_INVALID_ARGUMENT;
    }

    if (0U == rb->count)
    {
        return RING_BUFFER_STATUS_EMPTY;
    }

    *data = rb->buffer[rb->read_index];

    ++rb->read_index;

    if (rb->read_index >= rb->capacity)
    {
        rb->read_index = 0U;
    }

    --rb->count;

    return RING_BUFFER_STATUS_SUCCESS;
}