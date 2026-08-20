# String Copy

## Overview

This module implements a safe copy operation for null-terminated strings.

The purpose of the exercise is to practice string traversal, destination buffer
management and defensive programming in Embedded C.

The implementation copies the source string including its null terminator while
ensuring that the destination buffer is never accessed beyond its provided
capacity.

The implementation is expected to:

- Copy a null-terminated string into a destination buffer.
- Include the null terminator in the copied data.
- Validate all input arguments before accessing memory.
- Prevent destination buffer overflow.
- Detect when the destination buffer is too small.
- Keep the source string read-only.
- Avoid dynamic memory allocation.
- Return an explicit status value.
- Follow defensive programming and clean Embedded C coding practices.

The implementation should provide a small and reusable API suitable for copying
command strings, configuration values, protocol fields and other text data in
embedded software.

---

## Project Structure

```text
string_copy/
├── string_copy.c
└── string_copy.h
```