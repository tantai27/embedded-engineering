#ifndef TIMEOUT_COUNTER_H
#define TIMEOUT_COUNTER_H

#include <stdint.h>

/**
 * @brief Status returned by the timeout counter module.
 */
typedef enum
{
    TIMEOUT_COUNTER_STATUS_SUCCESS = 0U,
    TIMEOUT_COUNTER_STATUS_INVALID_ARGUMENT
} timeout_counter_status_t;

/**
 * @brief Timeout counter control structure.
 */
typedef struct
{
    uint32_t timeout;
    uint32_t elapsed;
    uint8_t running;
} timeout_counter_t;

/**
 * @brief Initialize a timeout counter.
 *
 * Initializes the timeout value and resets the elapsed time.
 *
 * @param[out] counter Pointer to the timeout counter structure.
 * @param[in] timeout Timeout duration in ticks.
 *
 * @retval TIMEOUT_COUNTER_STATUS_SUCCESS
 *         Timeout counter initialized successfully.
 *
 * @retval TIMEOUT_COUNTER_STATUS_INVALID_ARGUMENT
 *         Counter pointer is invalid or timeout is zero.
 */
timeout_counter_status_t timeout_counter_init(
    timeout_counter_t * const counter,
    uint32_t timeout);

/**
 * @brief Start the timeout counter.
 *
 * Resets the elapsed time and starts counting.
 *
 * @param[in,out] counter Pointer to the timeout counter structure.
 *
 * @retval TIMEOUT_COUNTER_STATUS_SUCCESS
 *         Timeout counter started successfully.
 *
 * @retval TIMEOUT_COUNTER_STATUS_INVALID_ARGUMENT
 *         Counter pointer is invalid.
 */
timeout_counter_status_t timeout_counter_start(
    timeout_counter_t * const counter);

/**
 * @brief Advance the timeout counter by one tick.
 *
 * The elapsed time is incremented only while the counter is running.
 * The elapsed value is saturated at the configured timeout.
 *
 * @param[in,out] counter Pointer to the timeout counter structure.
 *
 * @retval TIMEOUT_COUNTER_STATUS_SUCCESS
 *         Counter tick processed successfully.
 *
 * @retval TIMEOUT_COUNTER_STATUS_INVALID_ARGUMENT
 *         Counter pointer is invalid.
 */
timeout_counter_status_t timeout_counter_tick(
    timeout_counter_t * const counter);

/**
 * @brief Check whether the timeout has expired.
 *
 * @param[in] counter Pointer to the timeout counter structure.
 * @param[out] expired Pointer to store the expiration state.
 *
 * @retval TIMEOUT_COUNTER_STATUS_SUCCESS
 *         Expiration state returned successfully.
 *
 * @retval TIMEOUT_COUNTER_STATUS_INVALID_ARGUMENT
 *         One or more input arguments are invalid.
 */
timeout_counter_status_t timeout_counter_is_expired(
    const timeout_counter_t * const counter,
    uint8_t * const expired);

#endif