# String Compare

## Overview

This module implements a safe comparison of two null-terminated strings.

The purpose of the exercise is to practice character-by-character string
traversal, pointer handling and early termination in Embedded C.

The implementation compares both strings until a different character is found
or both strings reach the null terminator.

The implementation is expected to:

- Compare two null-terminated strings.
- Determine whether both strings contain identical characters.
- Stop immediately when a different character is detected.
- Validate input pointers before accessing memory.
- Keep both input strings read-only.
- Handle empty strings correctly.
- Avoid dynamic memory allocation.
- Return an explicit status value.
- Use defensive programming and clean Embedded C coding practices.

The implementation should provide a small and reusable API suitable for
comparing command strings, configuration values, protocol fields and other
null-terminated text data in embedded software.

---

## Project Structure

```text
string_compare/
├── string_compare.c
└── string_compare.h
```