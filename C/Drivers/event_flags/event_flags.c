#include <stddef.h>

#include "event_flags.h"

event_flags_status_t event_flags_init(
    event_flags_t * const event_flags)
{
    if (NULL == event_flags)
    {
        return EVENT_FLAGS_STATUS_INVALID_ARGUMENT;
    }

    event_flags->flags = 0U;

    return EVENT_FLAGS_STATUS_SUCCESS;
}

event_flags_status_t event_flags_set(
    event_flags_t * const event_flags,
    uint32_t mask)
{
    if (NULL == event_flags)
    {
        return EVENT_FLAGS_STATUS_INVALID_ARGUMENT;
    }

    event_flags->flags |= mask;

    return EVENT_FLAGS_STATUS_SUCCESS;
}

event_flags_status_t event_flags_clear(
    event_flags_t * const event_flags,
    uint32_t mask)
{
    if (NULL == event_flags)
    {
        return EVENT_FLAGS_STATUS_INVALID_ARGUMENT;
    }

    event_flags->flags &= ~mask;

    return EVENT_FLAGS_STATUS_SUCCESS;
}

event_flags_status_t event_flags_get(
    const event_flags_t * const event_flags,
    uint32_t * const flags)
{
    if ((NULL == event_flags) || (NULL == flags))
    {
        return EVENT_FLAGS_STATUS_INVALID_ARGUMENT;
    }

    *flags = event_flags->flags;

    return EVENT_FLAGS_STATUS_SUCCESS;
}

event_flags_status_t event_flags_are_set(
    const event_flags_t * const event_flags,
    uint32_t mask,
    uint8_t * const set)
{
    if ((NULL == event_flags) || (NULL == set))
    {
        return EVENT_FLAGS_STATUS_INVALID_ARGUMENT;
    }

    *set = ((event_flags->flags & mask) == mask) ? 1U : 0U;

    return EVENT_FLAGS_STATUS_SUCCESS;
}