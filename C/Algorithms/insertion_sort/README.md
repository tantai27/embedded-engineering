# Insertion Sort

A simple Embedded C implementation of the Insertion Sort algorithm for
sorting an array of 32-bit unsigned integers in ascending order.

## Overview

Insertion Sort builds the sorted portion of an array one element at a time.

For each element, the implementation stores the current value, shifts larger
elements in the already sorted portion one position to the right, and then
inserts the current value into its correct position.

The module operates directly on the caller-provided array and does not use
dynamic memory allocation.

## Features

- In-place ascending sort
- `uint32_t` data type
- Defensive argument validation
- No dynamic memory allocation
- Predictable memory usage
- Hardware-independent implementation
- Unit-testable API
- Efficient for small or nearly sorted data sets

## API

```c
insertion_sort_status_t insertion_sort(
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
| `INSERTION_SORT_STATUS_SUCCESS` | Sorting completed successfully |
| `INSERTION_SORT_STATUS_INVALID_ARGUMENT` | `data` is `NULL` while `length` is non-zero |

A `NULL` pointer with `length == 0` is accepted because no array access is
required.

## Algorithm

Insertion Sort divides the array conceptually into two regions:

```text
| sorted portion | unsorted portion |
```

Starting from the second element:

1. Store the current element as the value to insert.
2. Compare it with elements in the sorted portion.
3. Shift larger elements one position to the right.
4. Insert the stored value at the correct position.
5. Continue until the entire array is sorted.

Example:

```text
Input:
5  2  4  1  3

Insert 2:
2  5  4  1  3

Insert 4:
2  4  5  1  3

Insert 1:
1  2  4  5  3

Insert 3:
1  2  3  4  5
```

The left side of the array is always sorted before the next element is
inserted.

## Design

The implementation uses a temporary variable to preserve the element being
inserted:

```c
value = data[index];
```

Larger elements are shifted to the right:

```c
while ((position > 0U) &&
       (data[position - 1U] > value))
{
    data[position] = data[position - 1U];
    --position;
}
```

The saved value is then placed at the resulting position:

```c
data[position] = value;
```

The comparison uses `>` rather than `>=`, so elements with equal values are
not unnecessarily moved. This also preserves the relative ordering of equal
elements.

## Embedded C Considerations

### No Dynamic Memory

The module does not allocate or free memory. The caller owns the array
storage.

This makes memory usage deterministic and suitable for embedded systems with
fixed memory budgets.

### In-Place Operation

The array is sorted directly in the caller-provided memory.

Only a fixed number of local variables are required, so the additional
memory usage is constant.

### Defensive Argument Validation

The implementation rejects a `NULL` data pointer when the requested length
is non-zero.

Zero-length input is treated as a valid no-op.

### Fixed-Width Integer Types

`uint32_t` is used for array elements to make the element width explicit and
predictable across supported platforms.

`uint32_t` is also used for the array length and indices.

### Boundary Handling

The implementation handles:

- zero-length arrays
- single-element arrays
- two-element arrays
- duplicate values
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
| 4 | Already sorted | Validate already ordered input |
| 5 | Reverse sorted | Validate maximum shifting activity |
| 6 | Random values | Validate general sorting behavior |
| 7 | Duplicate values | Validate repeated elements |
| 8 | All values equal | Validate equal-value input |
| 9 | Two elements | Validate minimum sorting case |
| 10 | `uint32` boundaries | Validate minimum and maximum values |
| 11 | Nearly sorted values | Validate behavior on mostly ordered data |
| 12 | Mixed duplicates | Validate ordering with repeated values |

The test runner returns a non-zero exit status if any test fails.

## Build

Build the module with:

```text
[insertion_sort] $ make
CC      insertion_sort.c
CC      insertion_sort_test.c
LINK    insertion_sort_test
```

## Run

Run the complete unit-test suite:

```text
[insertion_sort] $ make run
./insertion_sort_test
========================================
Running insertion_sort unit tests
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
[11/12] Nearly sorted values         [PASS]
[12/12] Mixed duplicates             [PASS]
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
[insertion_sort] $ make clean
CLEAN   build artifacts
```

## Project Structure

```text
insertion_sort/
├── README.md
├── Makefile
├── insertion_sort.h
├── insertion_sort.c
└── insertion_sort_test.c
```

## Build Configuration

The module is built with:

- C11
- `-Wall`
- `-Wextra`
- `-Wpedantic`

The Makefile hides raw compiler commands from normal output while showing
the conceptual compilation and linking steps.

## Complexity

For an array containing `n` elements:

| Case | Time Complexity |
|------|-----------------|
| Best case | `O(n)` |
| Average case | `O(n²)` |
| Worst case | `O(n²)` |

The best case occurs when the input is already sorted or nearly sorted, as
very few elements need to be shifted.

### Space Complexity

```text
O(1)
```

The algorithm sorts the array in-place and requires only a fixed amount of
additional memory.

## Insertion Sort vs Bubble Sort

Both algorithms have `O(n²)` average and worst-case complexity and use
`O(1)` additional memory, but their operations differ.

| Property | Bubble Sort | Insertion Sort |
|----------|-------------|----------------|
| Main operation | Adjacent swaps | Element shifting |
| In-place | Yes | Yes |
| Extra memory | `O(1)` | `O(1)` |
| Best case | `O(n)` with early exit | `O(n)` |
| Nearly sorted data | Good | Often very good |
| Basic concept | Repeated adjacent comparison | Insert into sorted portion |

Insertion Sort is particularly useful when the input is already close to
being sorted because each new element may require only a small number of
shifts.

## Applications

Insertion Sort can be useful for:

- Small embedded data sets
- Small configuration tables
- Small buffers
- Maintaining small sorted collections
- Processing data that is already nearly sorted
- Educational implementations of sorting algorithms

For larger data sets, algorithms with better average-case scalability may be
more appropriate.

## Limitations

- `O(n²)` average and worst-case time complexity
- Performance degrades as the input size increases
- Supports `uint32_t` elements only
- Sorts in ascending order only
- Does not provide a generic comparator interface

## Repository Context

This module belongs to the `Algorithms` section of the Embedded C portfolio.

The current section contains both search and sorting algorithms:

```text
Algorithms/
├── linear_search/
├── binary_search/
├── bubble_sort/
└── insertion_sort/
```

The sorting implementations are intentionally introduced incrementally so
their algorithmic characteristics and implementation trade-offs can be
compared.

## Design Goals

The implementation prioritizes:

- Correctness
- Defensive programming
- Readability
- Predictable memory usage
- Simple API design
- Unit-testability
- Embedded-oriented coding practices