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
├── Makefile
├── README.md
├── string_compare.c
├── string_compare.h
└── string_compare_test.c
```

| File | Description |
|------|-------------|
| `string_compare.h` | Public API and string comparison status definitions. |
| `string_compare.c` | Null-terminated string comparison implementation. |
| `string_compare_test.c` | Unit tests for normal, boundary and invalid-argument cases. |
| `Makefile` | Build, run and clean targets. |
| `README.md` | Module documentation and test information. |

---

## API

```c
string_compare_status_t string_compare(const char * const lhs,
                                       const char * const rhs);
```

### Parameters

| Parameter | Description |
|-----------|-------------|
| `lhs` | Pointer to the first null-terminated string. |
| `rhs` | Pointer to the second null-terminated string. |

### Return Status

| Status | Description |
|--------|-------------|
| `STRING_COMPARE_STATUS_EQUAL` | Both strings contain identical characters. |
| `STRING_COMPARE_STATUS_NOT_EQUAL` | The strings contain different characters. |
| `STRING_COMPARE_STATUS_INVALID_ARGUMENT` | One or more input pointers are invalid. |

---

## Design Decisions

### Character-by-character comparison

The implementation traverses both strings simultaneously:

```text
lhs: h -> e -> l -> l -> o -> '\0'
rhs: h -> e -> l -> l -> o -> '\0'
     |    |    |    |    |
     +----+----+----+----+
              equal
```

The comparison stops as soon as a different character is detected.

### Null terminator

The comparison continues until:

```c
'\0'
```

is reached.

Two strings are considered equal only when both strings reach the null
terminator at the same position.

For example:

```text
"hello" vs "hello" -> EQUAL
"hello" vs "hell"  -> NOT_EQUAL
```

### Read-only input

Both input strings are declared as:

```c
const char * const
```

The implementation does not modify the caller's string data.

### Empty strings

Two empty strings:

```text
"" vs ""
```

are considered equal.

An empty string compared with a non-empty string is not equal.

### Defensive programming

The implementation validates both pointers before accessing memory.

Invalid input returns:

```text
STRING_COMPARE_STATUS_INVALID_ARGUMENT
```

This prevents dereferencing `NULL` pointers.

### No dynamic memory allocation

The implementation does not allocate or release memory.

Memory usage is deterministic and limited to the traversal pointers.

---

## Unit Tests

The unit tests verify:

- Equal strings.
- Different strings.
- Difference at the first character.
- Difference at the last character.
- Two empty strings.
- One empty string.
- Same prefix with different string lengths.
- `NULL` first pointer.
- `NULL` second pointer.

### Test Cases

```text
[01/09] Equal strings
[02/09] Different strings
[03/09] Different first character
[04/09] Different last character
[05/09] Empty strings
[06/09] One empty string
[07/09] Same prefix different length
[08/09] Null first pointer
[09/09] Null second pointer
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
make string_compare_test
```

The build produces:

```text
string_compare_test
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
Running string_compare unit tests
========================================
[01/09] Equal strings                [PASS]
[02/09] Different strings            [PASS]
[03/09] Different first character    [PASS]
[04/09] Different last character     [PASS]
[05/09] Empty strings                [PASS]
[06/09] One empty string             [PASS]
[07/09] Same prefix different length [PASS]
[08/09] Null first pointer           [PASS]
[09/09] Null second pointer          [PASS]
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
| `make string_compare_test` | Build the project explicitly. |
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
string_compare.o
string_compare_test.o
string_compare_test
```

---

## Concepts Practiced

- String comparison
- Null-terminated strings
- Character-by-character traversal
- Pointer traversal
- Null terminator handling
- Early termination
- First mismatch detection
- Empty string handling
- Pointer validation
- `const` correctness
- Defensive programming
- Explicit status reporting
- Static memory usage
- Unit testing
- Makefile
- Embedded C coding practices