#include <stddef.h>
#include <stdint.h>

#include "memory_compare.h"

memory_compare_status_t memory_compare(const void * const lhs,
                                       const void * const rhs,
                                       uint32_t size)
{
    const uint8_t *lhs_bytes = NULL;
    const uint8_t *rhs_bytes = NULL;
    uint32_t index = 0U;

    if ((NULL == lhs) || (NULL == rhs))
    {
        return MEMORY_COMPARE_STATUS_INVALID_ARGUMENT;
    }

    if (lhs == rhs)
    {
        return MEMORY_COMPARE_STATUS_EQUAL;
    }

    lhs_bytes = (const uint8_t *)lhs;
    rhs_bytes = (const uint8_t *)rhs;

    while (index < size)
    {
        if (lhs_bytes[index] != rhs_bytes[index])
        {
            return MEMORY_COMPARE_STATUS_NOT_EQUAL;
        }

        ++index;
    }

    return MEMORY_COMPARE_STATUS_EQUAL;
}