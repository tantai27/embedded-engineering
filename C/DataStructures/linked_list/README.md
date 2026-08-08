# Linked List

## Description

This module implements a simple singly linked list for storing 32-bit unsigned integer values.

The implementation is designed to practice fundamental data structure concepts together with common Embedded C programming practices, with emphasis on pointer safety, explicit status reporting and correct dynamic memory management.

The implementation is expected to:

- Initialize an empty linked list.
- Append nodes to the end of the list.
- Search for a value and return the corresponding node.
- Remove the first node containing a specified value.
- Release all allocated nodes and reset the list to an empty state.
- Validate pointer arguments before accessing memory.
- Handle dynamic memory allocation failure explicitly.
- Maintain correct ownership and lifetime of dynamically allocated nodes.
- Avoid memory leaks and dangling list references.
- Provide a simple API with explicit status reporting.

## Scope

The initial implementation focuses on a singly linked list containing `uint32_t` data.

The module intentionally keeps the API small so that the core concepts of linked lists, pointer traversal, insertion, removal and dynamic memory management remain clear and easy to study.

---

## Project Structure

```text
linked_list/
├── Makefile
├── README.md
├── linked_list.c
├── linked_list.h
└── linked_list_test.c
```

| File | Description |
|------|-------------|
| `linked_list.h` | Public API declaration and list node definition. |
| `linked_list.c` | Linked list implementation. |
| `linked_list_test.c` | Unit tests. |
| `Makefile` | Build, run and clean targets. |

---

## API

```c
list_status_t linked_list_init(list_node_t ** const head);

list_status_t linked_list_push_back(list_node_t ** const head,
                                     uint32_t data);

list_status_t linked_list_find(list_node_t * const head,
                               uint32_t data,
                               list_node_t ** const out_node);

list_status_t linked_list_remove(list_node_t ** const head,
                                  uint32_t data);

list_status_t linked_list_clear(list_node_t ** const head);
```

### Parameters

| Parameter | Description |
|-----------|-------------|
| `head` | Pointer to the list head pointer. |
| `data` | Value to insert, search for or remove. |
| `out_node` | Pointer used to return the matching node. |

### Return Value

| Value | Description |
|-------|-------------|
| `LIST_STATUS_SUCCESS` | Operation completed successfully. |
| `LIST_STATUS_NOT_FOUND` | Requested value does not exist in the list. |
| `LIST_STATUS_INVALID_ARGUMENT` | Invalid input pointer. |
| `LIST_STATUS_ALLOCATION_FAILED` | Dynamic memory allocation failed. |

---

## Design Decisions

- Use a singly linked list with `uint32_t` payload data.
- Store the `next` pointer explicitly in each node.
- Use `malloc()` when adding a new node.
- Check the result of every dynamic memory allocation before accessing the allocated object.
- Use explicit status codes to distinguish successful operations, invalid arguments, missing values and allocation failures.
- Keep the input list data unchanged during search operations.
- Remove only the first matching node when duplicate values exist.
- Release every allocated node through `linked_list_clear()`.
- Set the list head to `NULL` after clearing the list to avoid retaining a dangling head pointer.

---

## Unit Tests

The following scenarios are verified:

- Initialize an empty list.
- Insert the first node into an empty list.
- Insert multiple nodes and verify list traversal.
- Find an existing value.
- Handle a value that does not exist.
- Remove the head node.
- Remove a middle node.
- Handle removal of a missing value.
- Clear all nodes and reset the list.
- Reject a NULL head pointer.
- Reject a NULL output node pointer.

---

## Requirements

- GCC (C11 or later)
- GNU Make

Verify the tools are available:

```bash
gcc --version
make --version
```

---

## Build

Build the project:

```bash
make
```

or

```bash
make linked_list
```

---

## Run

Run all unit tests:

```bash
make run
```

### Expected Output

```text
========================================
Running linked_list unit tests
========================================
[01/11] Initialize empty list          [PASS]
[02/11] Push into empty list           [PASS]
[03/11] Push multiple nodes            [PASS]
[04/11] Find existing value            [PASS]
[05/11] Find missing value             [PASS]
[06/11] Remove head node               [PASS]
[07/11] Remove middle node             [PASS]
[08/11] Remove missing value           [PASS]
[09/11] Clear list                     [PASS]
[10/11] Null head pointer              [PASS]
[11/11] Null output node               [PASS]
----------------------------------------
Summary
----------------------------------------
Executed : 11/11
Passed   : 11/11 (100%)
Failed   : 0/11 (0%)
========================================
```

---

## Clean

Remove generated build artifacts:

```bash
make clean
```

---

## Concepts Practiced

- Singly linked list
- Structures
- Pointers to pointers
- Pointer traversal
- Dynamic memory allocation
- `malloc()` and `free()`
- Node insertion
- Node search
- Node removal
- Memory ownership
- Memory leak prevention
- Defensive programming
- Input validation
- Explicit status reporting
- Unit testing
- Makefile