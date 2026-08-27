# Buffer Copy

## Overview

This module implements a simple byte-buffer copy operation for embedded
software.

The purpose of the exercise is to practice low-level memory access, pointer
validation, buffer boundaries and overlap detection without relying on
dynamic memory allocation.

Unlike the standard `memcpy()` function, this implementation explicitly
detects overlapping source and destination regions and reports the condition
through a status code.

The implementation is expected to:

- Copy a specified number of bytes from a source buffer to a destination buffer.
- Keep the source buffer read-only.
- Validate source and destination pointers before accessing memory.
- Handle zero-length copy operations.
- Detect overlapping source and destination memory regions.
- Return an explicit status code for each operation.
- Use fixed-width integer types suitable for embedded systems.
- Avoid dynamic memory allocation.
- Follow defensive programming and clean Embedded C coding practices.

The module should provide a small and reusable API suitable for embedded
software that requires explicit control over memory-copy behavior.

---

## Project Structure

```text
buffer_copy/
├── buffer_copy.c
└── buffer_copy.h
```