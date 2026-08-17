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
├── linear_search.c
└── linear_search.h
```