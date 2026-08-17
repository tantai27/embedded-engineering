# Linear Search

## Overview

This module implements a linear search algorithm for an array of unsigned
32-bit integers.

The purpose of the exercise is to practice sequential array traversal and
target-value searching in Embedded C.

Unlike Binary Search, Linear Search does not require the input array to be
sorted. The implementation checks each element sequentially until the target
is found or all elements have been examined.

The implementation is expected to:

- Search for a target value sequentially.
- Support unsorted arrays.
- Return the index of the first matching element.
- Return an explicit status indicating the search result.
- Validate all input arguments before accessing memory.
- Keep the input array read-only.
- Avoid dynamic memory allocation.
- Use fixed-width integer types suitable for embedded systems.
- Follow defensive programming and clean Embedded C coding practices.

The implementation should provide a small and reusable API suitable for simple
search operations where the input data is unsorted or the dataset is small
enough that a sequential search is appropriate.

---

## Project Structure

```text
linear_search/
├── Makefile
├── README.md
├── linear_search.c
├── linear_search.h
└── linear_search_test.c
```

| File | Description |
|------|-------------|
| `linear_search.h` | Public API and search status definitions. |
| `linear_search.c` | Linear Search implementation. |
| `linear_search_test.c` | Unit tests for normal, boundary and invalid-argument cases. |
| `Makefile` | Build, run and clean targets. |
| `README.md` | Module documentation and test information. |

---

## API

```c
linear_search_status_t linear_search(const uint32_t * const arr,
                                     uint32_t size,
                                     uint32_t target,
                                     uint32_t * const out_index);
```

### Parameters

| Parameter | Description |
|-----------|-------------|
| `arr` | Pointer to the input array. |
| `size` | Number of elements in the array. |
| `target` | Value to search for. |
| `out_index` | Pointer to store the index of the first match. |

### Return Status

| Status | Description |
|--------|-------------|
| `LINEAR_SEARCH_STATUS_SUCCESS` | Target was found. |
| `LINEAR_SEARCH_STATUS_NOT_FOUND` | Target does not exist in the array. |
| `LINEAR_SEARCH_STATUS_INVALID_ARGUMENT` | One or more input arguments are invalid. |

---

## Design Decisions

### Sequential search

The algorithm checks elements from left to right:

```text
index 0 -> index 1 -> index 2 -> ... -> index N - 1
```

The function returns immediately when the target is found.

### Unsorted input

The input array does not need to be sorted.

For example:

```text
42  11  87  23  56
```

is a valid input for Linear Search.

This is the main practical difference from the Binary Search implementation.

### First occurrence

When the target appears multiple times, the function returns the index of
the first occurrence.

For example:

```text
Array:  10 20 30 20 40
Target: 20
```

The returned index is:

```text
1
```

### Read-only input

The input array is declared as:

```c
const uint32_t * const arr
```

The implementation does not modify the caller's array.

### Defensive programming

The implementation validates:

- `arr != NULL`
- `size != 0U`
- `out_index != NULL`

Invalid arguments return:

```text
LINEAR_SEARCH_STATUS_INVALID_ARGUMENT
```

before the array is accessed.

### No dynamic memory allocation

The implementation uses no heap allocation.

Memory usage remains deterministic and limited to local variables.

---

## Complexity

For an array containing `N` elements:

```text
Best case:    O(1)
Worst case:   O(N)
Space:        O(1)
```

The best case occurs when the target is the first element.

The worst case occurs when the target is the last element or does not exist.

---

## Unit Tests

The unit tests verify:

- Target found at the first element.
- Target found in the middle of the array.
- Target found at the last element.
- Target not found.
- Search in an unsorted array.
- First occurrence when duplicate values exist.
- Single-element array.
- `NULL` array pointer.
- Zero array size.

### Expected Test Cases

```text
[01/09] First element
[02/09] Middle element
[03/09] Last element
[04/09] Target not found
[05/09] Unsorted array
[06/09] First duplicate
[07/09] Single element
[08/09] Null array
[09/09] Zero array size
```

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

Build the unit test executable:

```bash
make
```

or:

```bash
make linear_search_test
```

The build produces:

```text
linear_search_test
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
Running linear_search unit tests
========================================
[01/09] First element                [PASS]
[02/09] Middle element              [PASS]
[03/09] Last element                [PASS]
[04/09] Target not found            [PASS]
[05/09] Unsorted array              [PASS]
[06/09] First duplicate             [PASS]
[07/09] Single element              [PASS]
[08/09] Null array                  [PASS]
[09/09] Zero array size             [PASS]
----------------------------------------
Summary
----------------------------------------
Executed : 9/9
Passed   : 9/9 (100%)
Failed   : 0/9 (0%)
========================================
```

A successful test run returns `EXIT_SUCCESS`.

If one or more tests fail, the test executable returns `EXIT_FAILURE`.

---

## Makefile Targets

| Target | Description |
|--------|-------------|
| `make` | Build the unit test executable. |
| `make linear_search_test` | Build the project explicitly. |
| `make run` | Build and execute all unit tests. |
| `make clean` | Remove generated build artifacts. |

---

## Clean

Remove generated build artifacts:

```bash
make clean
```

This removes:

```text
linear_search.o
linear_search_test.o
linear_search_test
```

---

## Concepts Practiced

- Linear Search
- Sequential array traversal
- Array indexing
- First-match detection
- Searching unsorted data
- Pointer validation
- `const` correctness
- Fixed-width integer types
- Defensive programming
- Explicit status reporting
- Algorithm complexity
- Static memory usage
- Unit testing
- Makefile
- Embedded C coding practices