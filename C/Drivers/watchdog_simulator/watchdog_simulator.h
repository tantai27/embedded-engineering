#ifndef WATCHDOG_SIMULATOR_H
#define WATCHDOG_SIMULATOR_H

#include <stdint.h>

/**
 * @brief Status returned by the watchdog simulator module.
 */
typedef enum
{
    WATCHDOG_SIMULATOR_STATUS_SUCCESS = 0U,
    WATCHDOG_SIMULATOR_STATUS_INVALID_ARGUMENT
} watchdog_simulator_status_t;

/**
 * @brief Watchdog simulator control structure.
 */
typedef struct
{
    uint32_t timeout;
    uint32_t elapsed;
    uint8_t running;
    uint8_t expired;
} watchdog_simulator_t;

/**
 * @brief Initialize the watchdog simulator.
 *
 * Initializes the watchdog timeout and resets its state.
 *
 * @param[out] watchdog Pointer to the watchdog control structure.
 * @param[in] timeout Timeout duration in ticks.
 *
 * @retval WATCHDOG_SIMULATOR_STATUS_SUCCESS
 *         Watchdog initialized successfully.
 *
 * @retval WATCHDOG_SIMULATOR_STATUS_INVALID_ARGUMENT
 *         Watchdog pointer is NULL or timeout is zero.
 */
watchdog_simulator_status_t watchdog_simulator_init(
    watchdog_simulator_t * const watchdog,
    uint32_t timeout);

/**
 * @brief Start the watchdog simulator.
 *
 * Resets the elapsed time and starts the watchdog.
 *
 * @param[in,out] watchdog Pointer to the watchdog control structure.
 *
 * @retval WATCHDOG_SIMULATOR_STATUS_SUCCESS
 *         Watchdog started successfully.
 *
 * @retval WATCHDOG_SIMULATOR_STATUS_INVALID_ARGUMENT
 *         Watchdog pointer is NULL.
 */
watchdog_simulator_status_t watchdog_simulator_start(
    watchdog_simulator_t * const watchdog);

/**
 * @brief Feed the watchdog simulator.
 *
 * Resets the elapsed time while keeping the watchdog running.
 *
 * @param[in,out] watchdog Pointer to the watchdog control structure.
 *
 * @retval WATCHDOG_SIMULATOR_STATUS_SUCCESS
 *         Watchdog fed successfully.
 *
 * @retval WATCHDOG_SIMULATOR_STATUS_INVALID_ARGUMENT
 *         Watchdog pointer is NULL.
 */
watchdog_simulator_status_t watchdog_simulator_feed(
    watchdog_simulator_t * const watchdog);

/**
 * @brief Advance the watchdog simulator by one tick.
 *
 * The elapsed time is incremented while the watchdog is running.
 * The watchdog becomes expired when the configured timeout is reached.
 *
 * @param[in,out] watchdog Pointer to the watchdog control structure.
 *
 * @retval WATCHDOG_SIMULATOR_STATUS_SUCCESS
 *         Tick processed successfully.
 *
 * @retval WATCHDOG_SIMULATOR_STATUS_INVALID_ARGUMENT
 *         Watchdog pointer is NULL.
 */
watchdog_simulator_status_t watchdog_simulator_tick(
    watchdog_simulator_t * const watchdog);

/**
 * @brief Check whether the watchdog has expired.
 *
 * @param[in] watchdog Pointer to the watchdog control structure.
 * @param[out] expired Pointer to store the expiration state.
 *
 * @retval WATCHDOG_SIMULATOR_STATUS_SUCCESS
 *         Expiration state returned successfully.
 *
 * @retval WATCHDOG_SIMULATOR_STATUS_INVALID_ARGUMENT
 *         One or more input arguments are invalid.
 */
watchdog_simulator_status_t watchdog_simulator_is_expired(
    const watchdog_simulator_t * const watchdog,
    uint8_t * const expired);

#endif