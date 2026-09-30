# Bubble Sort

A simple Embedded C implementation of the Bubble Sort algorithm for sorting
an array of 32-bit unsigned integers in ascending order.

## Overview

Bubble Sort repeatedly compares adjacent elements and swaps them when they
are in the wrong order.

This implementation includes an early-exit optimization: if a complete pass
performs no swaps, the array is already sorted and the algorithm stops.

The module is implemented without dynamic memory allocation and operates
directly on the caller-provided array.

## Scope

This module focuses on:

- Bubble Sort algorithm
- Array traversal and element swapping
- Boundary and length handling
- Early-exit optimization
- Defensive argument validation
- Unit-testable Embedded C implementation

## API

```c
bubble_sort_status_t bubble_sort(
    uint32_t * const data,
    uint32_t length);
```

The function sorts the input array in ascending order.

### Status Codes

| Status | Description |
|--------|-------------|
| `BUBBLE_SORT_STATUS_SUCCESS` | Sorting completed successfully |
| `BUBBLE_SORT_STATUS_INVALID_ARGUMENT` | Invalid input argument |

## Design Notes

- Input elements use `uint32_t`.
- Sorting is performed in-place.
- No dynamic memory allocation is required.
- A `NULL` data pointer is rejected when `length` is non-zero.
- Arrays with zero or one element require no sorting operation.
- The implementation uses an early-exit condition when no swap occurs
  during a complete pass.

## Complexity

| Case | Time Complexity |
|------|-----------------|
| Best case | `O(n)` |
| Average case | `O(n²)` |
| Worst case | `O(n²)` |

Space complexity: `O(1)`.

## Applications

Bubble Sort can be useful for:

- Small embedded data sets
- Simple configuration tables
- Small buffers where predictable in-place sorting is preferred
- Learning and demonstrating sorting algorithms

For larger data sets, more efficient algorithms such as Merge Sort or
Quick Sort may be more appropriate.

## Limitations

- Performance decreases quickly as the number of elements increases.
- The implementation sorts only `uint32_t` values.
- Sorting is performed in ascending order only.

## Repository Context

This module is part of the `Algorithms` section of the Embedded C
portfolio.

It complements the search algorithms implemented in this section and
provides a simple sorting algorithm for comparison with more advanced
sorting approaches.