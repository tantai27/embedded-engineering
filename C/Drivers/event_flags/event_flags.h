#ifndef EVENT_FLAGS_H
#define EVENT_FLAGS_H

#include <stdint.h>

/**
 * @brief Status returned by the event flags module.
 */
typedef enum
{
    EVENT_FLAGS_STATUS_SUCCESS = 0U,
    EVENT_FLAGS_STATUS_INVALID_ARGUMENT
} event_flags_status_t;

/**
 * @brief Event flags control structure.
 */
typedef struct
{
    uint32_t flags;
} event_flags_t;

/**
 * @brief Initialize the event flags object.
 *
 * Clears all event flags.
 *
 * @param[out] event_flags Pointer to the event flags control structure.
 *
 * @retval EVENT_FLAGS_STATUS_SUCCESS
 *         Event flags initialized successfully.
 *
 * @retval EVENT_FLAGS_STATUS_INVALID_ARGUMENT
 *         Event flags pointer is NULL.
 */
event_flags_status_t event_flags_init(
    event_flags_t * const event_flags);

/**
 * @brief Set one or more event flags.
 *
 * Sets all bits specified by the mask.
 *
 * @param[in,out] event_flags Pointer to the event flags control structure.
 * @param[in] mask Bit mask specifying the flags to set.
 *
 * @retval EVENT_FLAGS_STATUS_SUCCESS
 *         Event flags set successfully.
 *
 * @retval EVENT_FLAGS_STATUS_INVALID_ARGUMENT
 *         Event flags pointer is NULL.
 */
event_flags_status_t event_flags_set(
    event_flags_t * const event_flags,
    uint32_t mask);

/**
 * @brief Clear one or more event flags.
 *
 * Clears all bits specified by the mask.
 *
 * @param[in,out] event_flags Pointer to the event flags control structure.
 * @param[in] mask Bit mask specifying the flags to clear.
 *
 * @retval EVENT_FLAGS_STATUS_SUCCESS
 *         Event flags cleared successfully.
 *
 * @retval EVENT_FLAGS_STATUS_INVALID_ARGUMENT
 *         Event flags pointer is NULL.
 */
event_flags_status_t event_flags_clear(
    event_flags_t * const event_flags,
    uint32_t mask);

/**
 * @brief Get the current event flags.
 *
 * @param[in] event_flags Pointer to the event flags control structure.
 * @param[out] flags Pointer to store the current flags.
 *
 * @retval EVENT_FLAGS_STATUS_SUCCESS
 *         Current event flags returned successfully.
 *
 * @retval EVENT_FLAGS_STATUS_INVALID_ARGUMENT
 *         One or more input arguments are invalid.
 */
event_flags_status_t event_flags_get(
    const event_flags_t * const event_flags,
    uint32_t * const flags);

/**
 * @brief Check whether all requested event flags are set.
 *
 * @param[in] event_flags Pointer to the event flags control structure.
 * @param[in] mask Bit mask specifying the required flags.
 * @param[out] set Pointer to store the result.
 *
 * @retval EVENT_FLAGS_STATUS_SUCCESS
 *         Event flags checked successfully.
 *
 * @retval EVENT_FLAGS_STATUS_INVALID_ARGUMENT
 *         One or more input arguments are invalid.
 */
event_flags_status_t event_flags_are_set(
    const event_flags_t * const event_flags,
    uint32_t mask,
    uint8_t * const set);

#endif