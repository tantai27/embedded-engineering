#include <stddef.h>

#include "string_compare.h"

string_compare_status_t string_compare(const char * const lhs,
                                       const char * const rhs)
{
    const char *lhs_ptr = NULL;
    const char *rhs_ptr = NULL;

    if ((NULL == lhs) || (NULL == rhs))
    {
        return STRING_COMPARE_STATUS_INVALID_ARGUMENT;
    }

    lhs_ptr = lhs;
    rhs_ptr = rhs;

    while (('\0' != *lhs_ptr) && (*lhs_ptr == *rhs_ptr))
    {
        ++lhs_ptr;
        ++rhs_ptr;
    }

    if (*lhs_ptr == *rhs_ptr)
    {
        return STRING_COMPARE_STATUS_EQUAL;
    }

    return STRING_COMPARE_STATUS_NOT_EQUAL;
}