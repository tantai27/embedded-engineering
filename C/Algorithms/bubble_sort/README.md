# Bubble Sort

A simple Embedded C implementation of the Bubble Sort algorithm for sorting
an array of 32-bit unsigned integers in ascending order.

## Overview

Bubble Sort repeatedly compares adjacent elements and swaps them when they
are in the wrong order.

This implementation includes an early-exit optimization. If a complete pass
performs no swaps, the array is already sorted and the algorithm stops.

The module operates directly on the caller-provided array and does not use
dynamic memory allocation.

## Features

- In-place ascending sort
- `uint32_t` data type
- Early-exit optimization for already sorted data
- Defensive argument validation
- No dynamic memory allocation
- Deterministic control flow
- Hardware-independent implementation
- Unit-testable API

## API

```c
bubble_sort_status_t bubble_sort(
    uint32_t * const data,
    uint32_t length);
```

### Parameters

| Parameter | Direction | Description |
|-----------|-----------|-------------|
| `data` | `[in,out]` | Pointer to the array to be sorted |
| `length` | `[in]` | Number of elements in the array |

### Return Status

| Status | Description |
|--------|-------------|
| `BUBBLE_SORT_STATUS_SUCCESS` | Sorting completed successfully |
| `BUBBLE_SORT_STATUS_INVALID_ARGUMENT` | `data` is `NULL` while `length` is non-zero |

A `NULL` pointer with `length == 0` is accepted because no array access
is required.

## Algorithm

For each pass through the array:

1. Compare adjacent elements.
2. Swap them when the left element is greater than the right element.
3. Continue until the end of the unsorted portion.
4. If no swap occurs during a complete pass, terminate early.

For example:

```text
Input:
5  2  4  1  3

Pass 1:
2  4  1  3  5

Pass 2:
2  1  3  4  5

Pass 3:
1  2  3  4  5

Pass 4:
No swaps -> stop
```

The largest remaining element moves toward the end of the array during
each pass.

## Design

The implementation uses a temporary `uint32_t` variable for swapping:

```c
temp = data[index];
data[index] = data[index + 1U];
data[index + 1U] = temp;
```

The unsorted range becomes smaller after every pass, so the inner loop does
not revisit elements that are already in their final position.

The `swapped` flag provides the early-exit optimization for arrays that are
already sorted or become sorted before all possible passes are completed.

## Embedded C Considerations

### No Dynamic Memory

The module does not allocate or free memory. The caller owns the input
storage.

This makes memory usage predictable and suitable for embedded systems with
fixed memory budgets.

### In-Place Operation

The array is modified directly. Only a small fixed number of local
variables are required.

### Defensive Argument Validation

The implementation rejects:

- `NULL` data pointer with non-zero length

Zero-length input is treated as a valid no-op.

### Fixed-Width Integer Types

`uint32_t` is used to make the element width explicit and predictable
across supported platforms.

### Boundary Handling

The implementation handles:

- zero-length arrays
- single-element arrays
- two-element arrays
- `UINT32_MAX`
- `UINT32_MAX - 1U`

without requiring special caller-side handling.

## Unit Tests

The test suite contains 12 test cases.

| # | Test | Purpose |
|---|------|---------|
| 1 | NULL pointer | Validate invalid pointer handling |
| 2 | Zero length | Validate zero-length no-op |
| 3 | Single element | Validate single-element input |
| 4 | Already sorted | Validate sorted input and early exit |
| 5 | Reverse sorted | Validate maximum swap activity |
| 6 | Random values | Validate general sorting behavior |
| 7 | Duplicate values | Validate repeated elements |
| 8 | All values equal | Validate no-swap behavior |
| 9 | Two elements | Validate minimum sorting case |
| 10 | `uint32` boundaries | Validate minimum and maximum values |
| 11 | Mixed duplicates | Validate ordering with repeated values |
| 12 | Two element sorted input | Validate already ordered minimum case |

The test runner returns a non-zero exit status if any test fails.

## Build

Build the module with:

```text
[bubble_sort] $ make
CC      bubble_sort.c
CC      bubble_sort_test.c
LINK    bubble_sort_test
```

## Run

Run the complete unit-test suite:

```text
[bubble_sort] $ make run
./bubble_sort_test
========================================
Running bubble_sort unit tests
========================================
[01/12] NULL pointer                  [PASS]
[02/12] Zero length                  [PASS]
[03/12] Single element               [PASS]
[04/12] Already sorted               [PASS]
[05/12] Reverse sorted               [PASS]
[06/12] Random values                [PASS]
[07/12] Duplicate values             [PASS]
[08/12] All values equal             [PASS]
[09/12] Two elements                 [PASS]
[10/12] uint32 boundaries            [PASS]
[11/12] Mixed duplicates              [PASS]
[12/12] Two element sorted input     [PASS]
----------------------------------------
Summary
----------------------------------------
Executed : 12/12
Passed   : 12/12 (100%)
Failed   : 0/12 (0%)
========================================
```

## Clean

Remove generated object files and the test executable:

```text
[bubble_sort] $ make clean
CLEAN   build artifacts
```

## Project Structure

```text
bubble_sort/
├── README.md
├── Makefile
├── bubble_sort.h
├── bubble_sort.c
└── bubble_sort_test.c
```

## Build Configuration

The module is built with:

- C11
- `-Wall`
- `-Wextra`
- `-Wpedantic`

The build intentionally keeps compiler commands hidden from normal output
while displaying the conceptual compilation and linking steps.

## Complexity

For an array containing `n` elements:

| Case | Time Complexity |
|------|-----------------|
| Best case | `O(n)` |
| Average case | `O(n²)` |
| Worst case | `O(n²)` |

The best-case `O(n)` behavior is achieved by the early-exit optimization
when the input is already sorted.

### Space Complexity

```text
O(1)
```

The algorithm sorts the array in-place and uses only a fixed amount of
additional memory.

## Applications

Bubble Sort can be useful for:

- Small embedded data sets
- Small configuration tables
- Small buffers
- Educational implementations of sorting algorithms
- Situations where simple, predictable in-place behavior is more important
  than large-data performance

For larger data sets, more efficient algorithms such as Insertion Sort,
Merge Sort, or Quick Sort may be more appropriate.

## Limitations

- `O(n²)` average and worst-case time complexity
- Performance degrades as the input size increases
- Supports `uint32_t` elements only
- Sorts in ascending order only
- Does not provide a generic comparator interface

## Repository Context

This module belongs to the `Algorithms` section of the Embedded C
portfolio.

It complements the existing search algorithms:

```text
Algorithms/
├── linear_search/
├── binary_search/
└── bubble_sort/
```

The module provides a simple sorting implementation before introducing
more advanced sorting algorithms.

## Design Goals

The implementation prioritizes:

- Correctness
- Defensive programming
- Readability
- Predictable memory usage
- Simple API design
- Unit-testability
- Embedded-oriented coding practices