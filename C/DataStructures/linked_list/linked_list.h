#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stddef.h>
#include <stdint.h>

typedef enum
{
    LIST_STATUS_SUCCESS = 0U,
    LIST_STATUS_NOT_FOUND,
    LIST_STATUS_INVALID_ARGUMENT
} list_status_t;

typedef struct list_node
{
    uint32_t data;
    struct list_node *next;
} list_node_t;

/**
 * @brief Initialize an empty linked list.
 *
 * Sets the head pointer to NULL.
 *
 * @param[out] head Pointer to the list head.
 *
 * @retval LIST_STATUS_SUCCESS
 *         List initialized successfully.
 *
 * @retval LIST_STATUS_INVALID_ARGUMENT
 *         Invalid head pointer.
 */
list_status_t linked_list_init(list_node_t ** const head);

/**
 * @brief Append a node to the end of the linked list.
 *
 * Allocates a new node and stores the specified value.
 *
 * @param[in,out] head Pointer to the list head.
 * @param[in] data Value to append.
 *
 * @retval LIST_STATUS_SUCCESS
 *         Node added successfully.
 *
 * @retval LIST_STATUS_INVALID_ARGUMENT
 *         Invalid head pointer.
 *
 * @retval LIST_STATUS_NOT_FOUND
 *         Memory allocation failed.
 */
list_status_t linked_list_push_back(list_node_t ** const head,
                                     uint32_t data);

/**
 * @brief Find the first node containing the specified value.
 *
 * @param[in] head Pointer to the first node.
 * @param[in] data Value to search for.
 * @param[out] out_node Pointer to store the found node.
 *
 * @retval LIST_STATUS_SUCCESS
 *         Value found.
 *
 * @retval LIST_STATUS_NOT_FOUND
 *         Value does not exist in the list.
 *
 * @retval LIST_STATUS_INVALID_ARGUMENT
 *         Invalid output pointer.
 */
list_status_t linked_list_find(list_node_t * const head,
                               uint32_t data,
                               list_node_t ** const out_node);

/**
 * @brief Remove the first node containing the specified value.
 *
 * Frees the removed node.
 *
 * @param[in,out] head Pointer to the list head.
 * @param[in] data Value to remove.
 *
 * @retval LIST_STATUS_SUCCESS
 *         Node removed successfully.
 *
 * @retval LIST_STATUS_NOT_FOUND
 *         Value does not exist in the list.
 *
 * @retval LIST_STATUS_INVALID_ARGUMENT
 *         Invalid head pointer.
 */
list_status_t linked_list_remove(list_node_t ** const head,
                                  uint32_t data);

/**
 * @brief Free all nodes in the linked list.
 *
 * The list head is set to NULL after all nodes are released.
 *
 * @param[in,out] head Pointer to the list head.
 *
 * @retval LIST_STATUS_SUCCESS
 *         List released successfully.
 *
 * @retval LIST_STATUS_INVALID_ARGUMENT
 *         Invalid head pointer.
 */
list_status_t linked_list_clear(list_node_t ** const head);

#endif