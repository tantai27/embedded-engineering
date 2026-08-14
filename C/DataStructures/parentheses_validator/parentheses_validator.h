#ifndef PARENTHESES_VALIDATOR_H
#define PARENTHESES_VALIDATOR_H

#include <stdint.h>

/**
 * @brief Status returned by the parentheses_validator module.
 */
typedef enum
{
    PARENTHESES_STATUS_VALID = 0U,
    PARENTHESES_STATUS_INVALID,
    PARENTHESES_STATUS_INVALID_ARGUMENT,
    PARENTHESES_STATUS_OVERFLOW
} parentheses_status_t;

/**
 * @brief Validate the pairing and ordering of parentheses in a string.
 *
 * Supports the following bracket types:
 * (), [], {}
 *
 * A fixed-size internal stack is used to track opening brackets.
 *
 * @param[in]  str Pointer to the null-terminated input string.
 *
 * @retval PARENTHESES_STATUS_VALID
 *         All brackets are correctly matched and ordered.
 *
 * @retval PARENTHESES_STATUS_INVALID
 *         Brackets are incorrectly matched, ordered, or unclosed.
 *
 * @retval PARENTHESES_STATUS_INVALID_ARGUMENT
 *         Input string pointer is NULL.
 *
 * @retval PARENTHESES_STATUS_OVERFLOW
 *         The number of nested opening brackets exceeds the internal
 *         stack capacity.
 */
parentheses_status_t parentheses_validate(const char * const str);

#endif