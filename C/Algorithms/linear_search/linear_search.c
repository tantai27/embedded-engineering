#include <stddef.h>
#include <stdint.h>

#include "linear_search.h"

linear_search_status_t linear_search(const uint32_t * const arr,
                                     uint32_t size,
                                     uint32_t target,
                                     uint32_t * const out_index)
{
    uint32_t index = 0U;

    if ((NULL == arr) || (0U == size) || (NULL == out_index))
    {
        return LINEAR_SEARCH_STATUS_INVALID_ARGUMENT;
    }

    while (index < size)
    {
        if (target == arr[index])
        {
            *out_index = index;

            return LINEAR_SEARCH_STATUS_SUCCESS;
        }

        ++index;
    }

    return LINEAR_SEARCH_STATUS_NOT_FOUND;
}