#include <stddef.h>

#include "timeout_counter.h"

#define TIMEOUT_COUNTER_RUNNING (1U)
#define TIMEOUT_COUNTER_STOPPED (0U)

timeout_counter_status_t timeout_counter_init(
    timeout_counter_t * const counter,
    uint32_t timeout)
{
    if ((NULL == counter) || (0U == timeout))
    {
        return TIMEOUT_COUNTER_STATUS_INVALID_ARGUMENT;
    }

    counter->timeout = timeout;
    counter->elapsed = 0U;
    counter->running = TIMEOUT_COUNTER_STOPPED;

    return TIMEOUT_COUNTER_STATUS_SUCCESS;
}

timeout_counter_status_t timeout_counter_start(
    timeout_counter_t * const counter)
{
    if (NULL == counter)
    {
        return TIMEOUT_COUNTER_STATUS_INVALID_ARGUMENT;
    }

    counter->elapsed = 0U;
    counter->running = TIMEOUT_COUNTER_RUNNING;

    return TIMEOUT_COUNTER_STATUS_SUCCESS;
}

timeout_counter_status_t timeout_counter_tick(
    timeout_counter_t * const counter)
{
    if (NULL == counter)
    {
        return TIMEOUT_COUNTER_STATUS_INVALID_ARGUMENT;
    }

    if (TIMEOUT_COUNTER_RUNNING == counter->running)
    {
        if (counter->elapsed < counter->timeout)
        {
            ++counter->elapsed;
        }
        else
        {
            counter->running = TIMEOUT_COUNTER_STOPPED;
        }
    }

    return TIMEOUT_COUNTER_STATUS_SUCCESS;
}

timeout_counter_status_t timeout_counter_is_expired(
    const timeout_counter_t * const counter,
    uint8_t * const expired)
{
    if ((NULL == counter) || (NULL == expired))
    {
        return TIMEOUT_COUNTER_STATUS_INVALID_ARGUMENT;
    }

    *expired = (counter->elapsed >= counter->timeout) ? 1U : 0U;

    return TIMEOUT_COUNTER_STATUS_SUCCESS;
}