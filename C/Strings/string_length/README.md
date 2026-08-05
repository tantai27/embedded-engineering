# String Length

## Description

This module implements a safe API to calculate the length of a null-terminated string.

The implementation is designed following common Embedded C and Automotive software practices, with emphasis on robustness rather than simply reproducing the behavior of the standard library.

The implementation is expected to:

- Calculate the number of characters before the null terminator (`'\0'`).
- Validate all input arguments before accessing memory.
- Protect against integer overflow during length accumulation.
- Follow a defensive programming approach suitable for safety-critical software.
- Provide a simple, reusable API with explicit status reporting.


---

## Project Structure

```text
string_length/
├── Makefile
├── README.md
├── string_length.c
├── string_length.h
└── string_length_test.c
```

| File | Description |
|------|-------------|
| `string_length.h` | Public API declaration. |
| `string_length.c` | Function implementation. |
| `string_length_test.c` | Unit tests. |
| `Makefile` | Build, run and clean targets. |

---

## API

```c
str_status_t string_length(const char * const str,
                           uint32_t * const out_length);
```

### Parameters

| Parameter | Description |
|-----------|-------------|
| `str` | Pointer to the input string. |
| `out_length` | Pointer to store the calculated string length. |

### Return Value

| Value | Description |
|-------|-------------|
| `STR_STATUS_OK` | Operation completed successfully. |
| `STR_STATUS_ERR_PARAM` | Invalid input pointer. |
| `STR_STATUS_ERR_OVERFLOW` | String length exceeded the storage capacity of `uint32_t`. |

---

## Design Decisions

- Use `const` to guarantee that the input string is never modified.
- Validate all input arguments before accessing memory.
- Detect integer overflow during length accumulation.
- Return explicit status codes instead of relying on assertions or undefined behavior.
- Separate the traversal pointer from the original input pointer to preserve API safety.

---

## Unit Tests

The following scenarios are verified:

- Empty string
- Normal string
- String containing spaces
- Single-character string
- NULL input string
- NULL output pointer

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

```bash
make
```

or

```bash
make string_length
```

---

## Run

```bash
make run
```

### Expected Output

```text
========================================
Running string_length unit tests
========================================
[01/06] Empty string                  [PASS]
[02/06] Normal string                 [PASS]
[03/06] String with space             [PASS]
[04/06] Single character              [PASS]
[05/06] NULL string pointer           [PASS]
[06/06] NULL output pointer           [PASS]
----------------------------------------
Summary
----------------------------------------
Executed : 6/6
Passed   : 6/6 (100%)
Failed   : 0/6 (0%)
========================================
```

---

## Clean

```bash
make clean
```

---

## Concepts Practiced

- String traversal
- Null-terminated strings (`'\0'`)
- Pointer validation
- Integer overflow prevention
- Defensive programming
- `const` correctness
- Integer types (`uint32_t`)
- Basic unit testing
- Makefile