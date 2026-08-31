# String Reverse

## Overview

This module implements an in-place string reversal operation for Embedded C.

The purpose of the exercise is to practice string traversal, character
indexing, boundary handling and in-place data modification.

The implementation reverses a null-terminated string without allocating
additional memory for another string buffer.

The implementation is expected to:

- Reverse a null-terminated string in place.
- Handle empty strings safely.
- Validate the input pointer before accessing memory.
- Avoid dynamic memory allocation.
- Use fixed-width integer types for index management.
- Return an explicit status code.
- Follow defensive programming and clean Embedded C coding practices.

The module should provide a small and reusable API suitable for embedded
software that needs basic string manipulation with deterministic memory usage.

---

## Project Structure

```text
string_reverse/
├── string_reverse.c
└── string_reverse.h
```