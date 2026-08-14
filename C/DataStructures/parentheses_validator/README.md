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
├── Makefile
├── README.md
├── parentheses_validator.c
├── parentheses_validator.h
└── parentheses_validator_test.c
```

| File | Description |
|------|-------------|
| `parentheses_validator.h` | Public API and status definitions. |
| `parentheses_validator.c` | Parentheses validation and internal stack implementation. |
| `parentheses_validator_test.c` | Unit tests covering valid, invalid and boundary cases. |
| `Makefile` | Build, run and clean targets. |
| `README.md` | Module documentation and test information. |

---

## API

```c
parentheses_status_t parentheses_validate(const char * const str);
```

### Parameters

| Parameter | Description |
|-----------|-------------|
| `str` | Pointer to the null-terminated input string. |

### Return Status

| Status | Description |
|--------|-------------|
| `PARENTHESES_STATUS_VALID` | All supported brackets are correctly matched and ordered. |
| `PARENTHESES_STATUS_INVALID` | Brackets are mismatched, incorrectly ordered or unclosed. |
| `PARENTHESES_STATUS_INVALID_ARGUMENT` | The input string pointer is `NULL`. |
| `PARENTHESES_STATUS_OVERFLOW` | The nesting depth exceeds the internal stack capacity. |

---

## Supported Brackets

The validator recognizes three types of brackets:

```text
()    Parentheses
[]    Square brackets
{}    Curly brackets
```

Opening brackets are pushed onto the internal stack.

When a closing bracket is encountered, the most recently pushed opening
bracket is removed from the stack and checked for a matching pair.

For example:

```text
Input: {[()]}

{ -> push
[ -> push
( -> push
) -> pop (, match
] -> pop [, match
} -> pop {, match

Result: VALID
```

---

## Design Decisions

### Stack as an implementation detail

The purpose of this exercise is to demonstrate a practical use of a stack.

The stack is therefore kept private inside the implementation instead of
exposing generic `push`, `pop` and `peek` functions as part of the public API.

This keeps the public interface focused on the actual problem:

```text
string -> validation result
```

### Fixed-size stack

The internal stack uses statically allocated storage:

```c
char stack[PARENTHESES_STACK_CAPACITY];
```

No dynamic memory allocation is used.

This provides deterministic memory usage and avoids heap-related failure modes
in embedded environments.

### LIFO behavior

Opening brackets are stored in the order in which they are encountered.

For nested input:

```text
{[(
```

the stack contains:

```text
bottom -> { [ (
                 <- top
```

The closing `)` must therefore match `(` first.

This is the fundamental LIFO behavior required by the problem.

### Stack overflow protection

The implementation checks the stack capacity before pushing a new opening
bracket.

If the nesting depth exceeds the configured capacity, the function returns:

```text
PARENTHESES_STATUS_OVERFLOW
```

This prevents writing beyond the internal stack boundary.

### Input validation

The input pointer is checked before any memory access:

```c
if (NULL == str)
```

A `NULL` input returns:

```text
PARENTHESES_STATUS_INVALID_ARGUMENT
```

### Read-only input

The input parameter is declared as:

```c
const char * const str
```

The validator only reads the string and never modifies the caller's data.

### Non-bracket characters

Characters that are not one of the supported brackets are ignored.

For example:

```text
if (value[0] > 10)
```

is treated as valid because the bracket structure itself is valid.

The module is focused specifically on bracket matching rather than general
expression syntax validation.

---

## Validation Rules

The input is considered valid when:

1. Every opening bracket has a matching closing bracket.
2. Closing brackets appear in the correct order.
3. No closing bracket appears when the stack is empty.
4. The stack is empty after the complete string has been processed.

Examples:

```text
{[()]}       -> VALID
([{}])       -> VALID
()[]{}       -> VALID
hello()      -> VALID
```

Invalid examples:

```text
{[(])}       -> INVALID
([)]         -> INVALID
((())        -> INVALID
())          -> INVALID
]            -> INVALID
```

---

## Unit Tests

The unit test executable verifies normal operation, invalid input and
boundary conditions.

The test cases cover:

- Empty string.
- String without brackets.
- Simple matching pair.
- Multiple matching pairs.
- Correct nested brackets.
- Mismatched brackets.
- Incorrect bracket ordering.
- Unclosed opening bracket.
- Closing bracket without an opening bracket.
- `NULL` input pointer.
- Maximum supported nesting depth.
- Stack overflow.

### Test Case Examples

#### Valid nested brackets

```text
Input:  "{[()]}"

Expected:
PARENTHESES_STATUS_VALID
```

#### Mismatched brackets

```text
Input:  "{[(])}"

Expected:
PARENTHESES_STATUS_INVALID
```

#### Unclosed brackets

```text
Input:  "((("

Expected:
PARENTHESES_STATUS_INVALID
```

#### Closing bracket without opening bracket

```text
Input:  "}"

Expected:
PARENTHESES_STATUS_INVALID
```

#### Maximum nesting depth

The test constructs an input containing exactly
`PARENTHESES_STACK_CAPACITY` nested opening brackets followed by the matching
closing brackets.

This verifies that the highest valid stack depth is accepted.

#### Stack overflow

The test constructs an input containing more than
`PARENTHESES_STACK_CAPACITY` nested opening brackets.

The expected result is:

```text
PARENTHESES_STATUS_OVERFLOW
```

This verifies that the implementation does not write beyond the internal
stack boundary.

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
make parentheses_validator
```

The build produces:

```text
parentheses_validator_test
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
Running parentheses_validator unit tests
========================================
[01/12] Empty string                 [PASS]
[02/12] No brackets                 [PASS]
[03/12] Simple pair                 [PASS]
[04/12] Multiple pairs              [PASS]
[05/12] Nested brackets             [PASS]
[06/12] Mismatched brackets         [PASS]
[07/12] Incorrect ordering          [PASS]
[08/12] Unclosed brackets           [PASS]
[09/12] Unexpected closing bracket  [PASS]
[10/12] Null input                  [PASS]
[11/12] Maximum nesting depth       [PASS]
[12/12] Stack overflow              [PASS]
----------------------------------------
Summary
----------------------------------------
Executed : 12/12
Passed   : 12/12 (100%)
Failed   : 0/12 (0%)
========================================
```

A successful test run returns `EXIT_SUCCESS`.

If one or more tests fail, the test executable returns `EXIT_FAILURE`.

This makes the test executable suitable for later integration into an
automated build or CI pipeline.

---

## Makefile Targets

| Target | Description |
|--------|-------------|
| `make` | Build the unit test executable. |
| `make parentheses_validator` | Build the project explicitly. |
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
parentheses_validator.o
parentheses_validator_test.o
parentheses_validator_test
```

---

## Concepts Practiced

- Stack / LIFO
- Fixed-size data structures
- Nested structure validation
- String traversal
- Character comparison
- Bracket matching
- Stack overflow protection
- Boundary checking
- Defensive programming
- Pointer validation
- `const` correctness
- Fixed-width integer types
- Static memory allocation
- Explicit status reporting
- Unit testing
- Makefile