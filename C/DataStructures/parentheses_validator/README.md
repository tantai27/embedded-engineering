# Parentheses Validator

## Overview

This module validates the pairing and ordering of brackets in a
null-terminated string.

The exercise uses a fixed-size stack to track opening brackets while scanning
the input string from left to right.

The validator supports the following bracket types:

- Parentheses: `()`
- Square brackets: `[]`
- Curly brackets: `{}`

The purpose of the exercise is to practice a practical use of the LIFO
data-structure pattern rather than implementing a standalone stack API.

The implementation is expected to:

- Validate correctly matched and ordered brackets.
- Detect mismatched closing brackets.
- Detect closing brackets without a corresponding opening bracket.
- Detect unclosed opening brackets.
- Use a fixed-size stack without dynamic memory allocation.
- Detect stack capacity overflow caused by excessive nesting.
- Validate the input pointer before accessing memory.
- Keep the input string read-only.
- Process the string sequentially until the null terminator.
- Return explicit status values for valid, invalid and erroneous conditions.
- Follow defensive programming and clean Embedded C coding practices.

The implementation should provide a small and deterministic API suitable for
embedded software where dynamic memory allocation is avoided.

---

## Project Structure

```text
parentheses_validator/
├── README.md
├── parentheses_validator.c
└── parentheses_validator.h
```

---

## Concepts Practiced

- Stack / LIFO
- Fixed-size data structures
- Character-by-character string traversal
- Bracket matching
- Nested structure validation
- Boundary checking
- Defensive programming
- Pointer validation
- `const` correctness
- Fixed-width integer types
- Static memory allocation
- Explicit status reporting