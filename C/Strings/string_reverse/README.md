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
├── Makefile
├── README.md
├── string_reverse.c
├── string_reverse.h
└── string_reverse_test.c
```

| File | Description |
|------|-------------|
| `string_reverse.h` | Public API and string reverse status definitions. |
| `string_reverse.c` | In-place string reversal implementation. |
| `string_reverse_test.c` | Unit tests for normal strings, boundaries and invalid arguments. |
| `Makefile` | Build, run and clean targets. |
| `README.md` | Module documentation and test information. |

---

## API

```c
string_reverse_status_t string_reverse(
    char * const string);
```

### Parameters

| Parameter | Description |
|-----------|-------------|
| `string` | Pointer to the null-terminated string to reverse. |

The input buffer must be writable because the operation modifies the string
in place.

---

## Return Status

| Status | Description |
|--------|-------------|
| `STRING_REVERSE_STATUS_SUCCESS` | String reversed successfully. |
| `STRING_REVERSE_STATUS_INVALID_ARGUMENT` | String pointer is invalid. |

---

## Design Decisions

### In-place reversal

The string is reversed directly inside the original buffer.

For example:

```text
Before:

+---+---+---+---+---+---+
| A | B | C | D | E | \0|
+---+---+---+---+---+---+

After:

+---+---+---+---+---+---+
| E | D | C | B | A | \0|
+---+---+---+---+---+---+
```

No second string buffer is required.

### Two-index approach

The implementation uses two indices:

```text
left
right
```

The characters at both positions are swapped repeatedly:

```text
left ->        <- right

A B C D E
^         ^

E B C D A
  ^     ^

E D C B A
```

The process stops when the two indices meet or cross.

### Null terminator

The null terminator is not moved.

The implementation first determines the string length by searching for:

```c
'\0'
```

The final character index is then:

```text
length - 1
```

This ensures that only actual string characters are reversed.

### Empty string

An empty string is valid:

```c
char string[] = "";
```

The function returns success without modifying the buffer.

### Single-character string

A single-character string is also valid.

There is no swap required because both ends refer to the same character.

For example:

```text
"A" -> "A"
```

### Defensive programming

The implementation validates the string pointer before accessing memory.

A `NULL` pointer returns:

```text
STRING_REVERSE_STATUS_INVALID_ARGUMENT
```

No memory access is performed for an invalid pointer.

### No dynamic memory allocation

The implementation does not use:

```text
malloc()
calloc()
realloc()
free()
```

The caller provides the writable string buffer.

This keeps memory usage deterministic and suitable for embedded systems.

---

## Complexity

For a string containing `n` characters:

```text
Time complexity  : O(n)
Space complexity : O(1)
```

The string must be traversed once to determine its length, followed by at
most `n / 2` character swaps.

Only a small number of local variables are required.

---

## Unit Tests

The unit tests verify:

- Normal string reversal.
- Single-character string.
- Two-character string.
- Even-length string.
- Odd-length string.
- String containing spaces.
- Empty string.
- String containing numbers.
- `NULL` pointer handling.

### Test Cases

```text
[01/09] Reverse normal string
[02/09] Reverse single character
[03/09] Reverse two characters
[04/09] Reverse even length
[05/09] Reverse odd length
[06/09] Reverse string with spaces
[07/09] Reverse empty string
[08/09] Reverse string with numbers
[09/09] Null pointer
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
make string_reverse_test
```

The build produces:

```text
string_reverse_test
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
Running string_reverse unit tests
========================================
[01/09] Reverse normal string        [PASS]
[02/09] Reverse single character    [PASS]
[03/09] Reverse two characters      [PASS]
[04/09] Reverse even length         [PASS]
[05/09] Reverse odd length          [PASS]
[06/09] Reverse string with spaces  [PASS]
[07/09] Reverse empty string        [PASS]
[08/09] Reverse string with numbers [PASS]
[09/09] Null pointer                [PASS]
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
| `make string_reverse_test` | Build the project explicitly. |
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
string_reverse.o
string_reverse_test.o
string_reverse_test
```

---

## Concepts Practiced

- String traversal
- Null-terminated strings
- Character indexing
- In-place modification
- Two-index traversal
- Character swapping
- Boundary conditions
- Empty-string handling
- `NULL` pointer validation
- `char`
- `uint32_t`
- Deterministic memory usage
- Constant auxiliary space
- Defensive programming
- Explicit status reporting
- Unit testing
- Makefile
- Embedded C coding practices