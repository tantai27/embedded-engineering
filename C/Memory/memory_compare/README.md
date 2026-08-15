# Memory Compare

## Overview

This module implements a safe byte-by-byte comparison of two memory regions.

The purpose of the exercise is to practice low-level memory access and pointer
handling in Embedded C while maintaining a small and deterministic API.

The implementation is expected to:

- Compare two memory regions byte by byte.
- Determine whether the specified memory regions contain identical data.
- Accept generic memory pointers through `const void *`.
- Treat both input memory regions as read-only.
- Validate input pointers before accessing memory.
- Handle zero-length comparisons deterministically.
- Detect the special case where both pointers refer to the same memory region.
- Avoid modifying either input memory region.
- Avoid dynamic memory allocation.
- Use fixed-width integer types suitable for embedded systems.
- Return an explicit status value indicating the comparison result.
- Follow defensive programming and clean Embedded C coding practices.

The implementation should provide a small and reusable API suitable for
comparing buffers, communication payloads, memory blocks and other byte-oriented
data in embedded software.

---

## Project Structure

```text
memory_compare/
├── memory_compare.c
└── memory_compare.h
```