# Binary Search

## Description

This module implements a safe Binary Search API for searching a value in an ascending sorted array.

The implementation is designed following common Embedded C and Automotive software practices, with emphasis on correctness, robustness and defensive programming rather than simply implementing the algorithm.

The implementation is expected to:

- Search for a target value in an ascending sorted array.
- Return both execution status and the found index through an output parameter.
- Validate all input arguments before accessing memory.
- Prevent unsigned integer overflow when calculating the middle index.
- Prevent unsigned underflow during boundary updates.
- Follow a defensive programming approach suitable for safety-critical software.
- Provide a simple, reusable API with explicit status reporting.

---

## Project Structure

```text
binary_search/
├── Makefile
├── README.md
├── binary_search.c
├── binary_search.h
└── binary_search_test.c
```

| File | Description |
|------|-------------|
| `binary_search.h` | Public API declaration. |
| `binary_search.c` | Function implementation. |
| `binary_search_test.c` | Unit tests. |
| `Makefile` | Build, run and clean targets. |

---

## API

```c
search_status_t binary_search(const uint32_t * const array,
                              uint32_t size,
                              uint32_t target,
                              uint32_t * const out_index);
```

### Parameters

| Parameter | Description |
|-----------|-------------|
| `array` | Pointer to a sorted array. |
| `size` | Number of elements in the array. |
| `target` | Value to search. |
| `out_index` | Pointer to store the index if found. |

### Return Value

| Value | Description |
|-------|-------------|
| `SEARCH_STATUS_OK` | Target found successfully. |
| `SEARCH_STATUS_NOT_FOUND` | Target does not exist. |
| `SEARCH_STATUS_ERR_PARAM` | Invalid input parameter. |
| `SEARCH_STATUS_ERR_OVERFLOW` | Overflow detected while computing the middle index. |

---

## Design Decisions

- Accept only sorted arrays.
- Validate every input argument.
- Compute the middle index using:

```c
left + ((right - left) >> 1U)
```

to avoid integer overflow.

- Protect against unsigned underflow when updating the search range.
- Return explicit status codes instead of using sentinel values.

---

## Unit Tests

The following scenarios are verified:

- Find first element
- Find last element
- Find middle element
- Target not found
- NULL array pointer
- Zero array size
- NULL output pointer

---

## Requirements

- GCC (C11 or later)
- GNU Make

```bash
gcc --version
make --version
```

---

## Build

```bash
make
```

or

```bash
make binary_search
```

---

## Run

```bash
make run
```

### Expected Output

```text
========================================
Running binary_search unit tests
========================================
[01/07] Find first element             [PASS]
[02/07] Find last element              [PASS]
[03/07] Find middle element            [PASS]
[04/07] Target not found               [PASS]
[05/07] NULL array pointer             [PASS]
[06/07] Zero array size                [PASS]
[07/07] NULL output pointer            [PASS]
----------------------------------------
Summary
----------------------------------------
Executed : 7/7
Passed   : 7/7 (100%)
Failed   : 0/7 (0%)
========================================
```

---

## Clean

```bash
make clean
```

---

## Concepts Practiced

- Binary Search
- Divide and Conquer
- Defensive Programming
- Input Validation
- Integer Overflow Prevention
- Unsigned Underflow Prevention
- Pointer Validation
- Constant Pointer
- Unit Testing
- Makefile