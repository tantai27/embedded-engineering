#include <stddef.h>

#include "debounce.h"

#define DEBOUNCE_STATE_LOW     (0U)
#define DEBOUNCE_STATE_HIGH    (1U)

debounce_status_t debounce_init(
    debounce_t * const debounce,
    uint8_t initial_state,
    uint32_t stable_ticks)
{
    if ((NULL == debounce) ||
        (0U == stable_ticks) ||
        ((DEBOUNCE_STATE_LOW != initial_state) &&
         (DEBOUNCE_STATE_HIGH != initial_state)))
    {
        return DEBOUNCE_STATUS_INVALID_ARGUMENT;
    }

    debounce->stable_ticks = stable_ticks;
    debounce->consecutive_ticks = 0U;
    debounce->stable_state = initial_state;
    debounce->candidate_state = initial_state;

    return DEBOUNCE_STATUS_SUCCESS;
}

debounce_status_t debounce_update(
    debounce_t * const debounce,
    uint8_t raw_state,
    uint8_t * const stable_state)
{
    if ((NULL == debounce) ||
        (NULL == stable_state) ||
        ((DEBOUNCE_STATE_LOW != raw_state) &&
         (DEBOUNCE_STATE_HIGH != raw_state)))
    {
        return DEBOUNCE_STATUS_INVALID_ARGUMENT;
    }

    if (raw_state != debounce->candidate_state)
    {
        debounce->candidate_state = raw_state;
        debounce->consecutive_ticks = 1U;
    }
    else if (debounce->consecutive_ticks <
             debounce->stable_ticks)
    {
        ++debounce->consecutive_ticks;
    }

    if (debounce->consecutive_ticks >= debounce->stable_ticks)
    {
        debounce->stable_state = debounce->candidate_state;
    }

    *stable_state = debounce->stable_state;

    return DEBOUNCE_STATUS_SUCCESS;
}