#include <stddef.h>
#include <stdint.h>

#include "binary_search.h"

search_status_t binary_search(const uint32_t * const arr,
                              uint32_t size,
                              uint32_t target,
                              uint32_t * const out_index)
{
    uint32_t left = 0U;
    uint32_t right = 0U;
    uint32_t mid = 0U;

    if ((NULL == arr) ||
        (0U == size) ||
        (NULL == out_index))
    {
        return SEARCH_STATUS_INVALID_ARGUMENT;
    }

    right = size - 1U;

    while (left <= right)
    {
        /* Compute midpoint without overflowing uint32_t. */
        mid = left + ((right - left) >> 1U);

        if (target == arr[mid])
        {
            *out_index = mid;
            return SEARCH_STATUS_SUCCESS;
        }

        if (target < arr[mid])
        {
            /*
             * Prevent unsigned underflow when mid is zero.
             */
            if (0U == mid)
            {
                break;
            }

            right = mid - 1U;
        }
        else
        {
            left = mid + 1U;
        }
    }

    return SEARCH_STATUS_NOT_FOUND;
}