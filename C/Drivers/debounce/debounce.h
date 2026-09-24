#ifndef DEBOUNCE_H
#define DEBOUNCE_H

#include <stdint.h>

/**
 * @brief Status returned by the debounce module.
 */
typedef enum
{
    DEBOUNCE_STATUS_SUCCESS = 0U,
    DEBOUNCE_STATUS_INVALID_ARGUMENT
} debounce_status_t;

/**
 * @brief Debounce state.
 */
typedef struct
{
    uint32_t stable_ticks;
    uint32_t consecutive_ticks;
    uint8_t stable_state;
    uint8_t candidate_state;
} debounce_t;

/**
 * @brief Initialize a debounce instance.
 *
 * @param[out] debounce Pointer to the debounce instance.
 * @param[in] initial_state Initial stable input state.
 * @param[in] stable_ticks Number of consecutive samples required
 *                         before accepting a new state.
 *
 * @retval DEBOUNCE_STATUS_SUCCESS
 *         Debounce instance initialized successfully.
 *
 * @retval DEBOUNCE_STATUS_INVALID_ARGUMENT
 *         The debounce pointer is NULL, or stable_ticks is zero.
 */
debounce_status_t debounce_init(
    debounce_t * const debounce,
    uint8_t initial_state,
    uint32_t stable_ticks);

/**
 * @brief Update the debounce state with a raw input sample.
 *
 * A new state is accepted only after the raw input remains unchanged
 * for the configured number of consecutive ticks.
 *
 * @param[in,out] debounce Pointer to the debounce instance.
 * @param[in] raw_state Current raw input state.
 * @param[out] stable_state Pointer to store the debounced state.
 *
 * @retval DEBOUNCE_STATUS_SUCCESS
 *         Debounce state updated successfully.
 *
 * @retval DEBOUNCE_STATUS_INVALID_ARGUMENT
 *         The debounce pointer or stable_state pointer is NULL.
 */
debounce_status_t debounce_update(
    debounce_t * const debounce,
    uint8_t raw_state,
    uint8_t * const stable_state);

#endif