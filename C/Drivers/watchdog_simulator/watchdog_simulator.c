#include <stddef.h>

#include "watchdog_simulator.h"

#define WATCHDOG_SIMULATOR_RUNNING  (1U)
#define WATCHDOG_SIMULATOR_STOPPED  (0U)
#define WATCHDOG_SIMULATOR_EXPIRED  (1U)
#define WATCHDOG_SIMULATOR_ACTIVE   (0U)

watchdog_simulator_status_t watchdog_simulator_init(
    watchdog_simulator_t * const watchdog,
    uint32_t timeout)
{
    if ((NULL == watchdog) || (0U == timeout))
    {
        return WATCHDOG_SIMULATOR_STATUS_INVALID_ARGUMENT;
    }

    watchdog->timeout = timeout;
    watchdog->elapsed = 0U;
    watchdog->running = WATCHDOG_SIMULATOR_STOPPED;
    watchdog->expired = WATCHDOG_SIMULATOR_ACTIVE;

    return WATCHDOG_SIMULATOR_STATUS_SUCCESS;
}

watchdog_simulator_status_t watchdog_simulator_start(
    watchdog_simulator_t * const watchdog)
{
    if (NULL == watchdog)
    {
        return WATCHDOG_SIMULATOR_STATUS_INVALID_ARGUMENT;
    }

    watchdog->elapsed = 0U;
    watchdog->running = WATCHDOG_SIMULATOR_RUNNING;
    watchdog->expired = WATCHDOG_SIMULATOR_ACTIVE;

    return WATCHDOG_SIMULATOR_STATUS_SUCCESS;
}

watchdog_simulator_status_t watchdog_simulator_feed(
    watchdog_simulator_t * const watchdog)
{
    if (NULL == watchdog)
    {
        return WATCHDOG_SIMULATOR_STATUS_INVALID_ARGUMENT;
    }

    if (WATCHDOG_SIMULATOR_RUNNING == watchdog->running)
    {
        watchdog->elapsed = 0U;
        watchdog->expired = WATCHDOG_SIMULATOR_ACTIVE;
    }

    return WATCHDOG_SIMULATOR_STATUS_SUCCESS;
}

watchdog_simulator_status_t watchdog_simulator_tick(
    watchdog_simulator_t * const watchdog)
{
    if (NULL == watchdog)
    {
        return WATCHDOG_SIMULATOR_STATUS_INVALID_ARGUMENT;
    }

    if (WATCHDOG_SIMULATOR_RUNNING == watchdog->running)
    {
        if (watchdog->elapsed < watchdog->timeout)
        {
            ++watchdog->elapsed;
        }

        if (watchdog->elapsed >= watchdog->timeout)
        {
            watchdog->expired = WATCHDOG_SIMULATOR_EXPIRED;
            watchdog->running = WATCHDOG_SIMULATOR_STOPPED;
        }
    }

    return WATCHDOG_SIMULATOR_STATUS_SUCCESS;
}

watchdog_simulator_status_t watchdog_simulator_is_expired(
    const watchdog_simulator_t * const watchdog,
    uint8_t * const expired)
{
    if ((NULL == watchdog) || (NULL == expired))
    {
        return WATCHDOG_SIMULATOR_STATUS_INVALID_ARGUMENT;
    }

    *expired = watchdog->expired;

    return WATCHDOG_SIMULATOR_STATUS_SUCCESS;
}