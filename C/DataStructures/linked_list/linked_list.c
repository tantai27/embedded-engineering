#include <stdlib.h>

#include "linked_list.h"

list_status_t linked_list_init(list_node_t ** const head)
{
    if (NULL == head)
    {
        return LIST_STATUS_INVALID_ARGUMENT;
    }

    *head = NULL;

    return LIST_STATUS_SUCCESS;
}

list_status_t linked_list_push_back(list_node_t ** const head,
                                     uint32_t data)
{
    list_node_t *new_node = NULL;
    list_node_t *current = NULL;

    if (NULL == head)
    {
        return LIST_STATUS_INVALID_ARGUMENT;
    }

    new_node = (list_node_t *)malloc(sizeof(list_node_t));

    if (NULL == new_node)
    {
        return LIST_STATUS_NOT_FOUND;
    }

    new_node->data = data;
    new_node->next = NULL;

    if (NULL == *head)
    {
        *head = new_node;
    }
    else
    {
        current = *head;

        while (NULL != current->next)
        {
            current = current->next;
        }

        current->next = new_node;
    }

    return LIST_STATUS_SUCCESS;
}

list_status_t linked_list_find(list_node_t * const head,
                               uint32_t data,
                               list_node_t ** const out_node)
{
    list_node_t *current = NULL;

    if (NULL == out_node)
    {
        return LIST_STATUS_INVALID_ARGUMENT;
    }

    current = head;

    while (NULL != current)
    {
        if (data == current->data)
        {
            *out_node = current;
            return LIST_STATUS_SUCCESS;
        }

        current = current->next;
    }

    *out_node = NULL;

    return LIST_STATUS_NOT_FOUND;
}

list_status_t linked_list_remove(list_node_t ** const head,
                                  uint32_t data)
{
    list_node_t *current = NULL;
    list_node_t *previous = NULL;

    if (NULL == head)
    {
        return LIST_STATUS_INVALID_ARGUMENT;
    }

    current = *head;

    while (NULL != current)
    {
        if (data == current->data)
        {
            if (NULL == previous)
            {
                *head = current->next;
            }
            else
            {
                previous->next = current->next;
            }

            free(current);

            return LIST_STATUS_SUCCESS;
        }

        previous = current;
        current = current->next;
    }

    return LIST_STATUS_NOT_FOUND;
}

list_status_t linked_list_clear(list_node_t ** const head)
{
    list_node_t *current = NULL;
    list_node_t *next = NULL;

    if (NULL == head)
    {
        return LIST_STATUS_INVALID_ARGUMENT;
    }

    current = *head;

    while (NULL != current)
    {
        next = current->next;
        free(current);
        current = next;
    }

    *head = NULL;

    return LIST_STATUS_SUCCESS;
}