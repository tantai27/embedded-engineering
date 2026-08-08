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