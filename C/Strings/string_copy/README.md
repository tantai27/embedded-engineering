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
├── Makefile
├── README.md
├── string_copy.c
├── string_copy.h
└── string_copy_test.c
```

| File | Description |
|------|-------------|
| `string_copy.h` | Public API and string copy status definitions. |
| `string_copy.c` | Safe null-terminated string copy implementation. |
| `string_copy_test.c` | Unit tests for normal, boundary and invalid-argument cases. |
| `Makefile` | Build, run and clean targets. |
| `README.md` | Module documentation and test information. |

---

## API

```c
string_copy_status_t string_copy(char * const dest,
                                 uint32_t dest_size,
                                 const char * const src);
```

### Parameters

| Parameter | Description |
|-----------|-------------|
| `dest` | Pointer to the destination buffer. |
| `dest_size` | Capacity of the destination buffer in bytes. |
| `src` | Pointer to the source null-terminated string. |

### Return Status

| Status | Description |
|--------|-------------|
| `STRING_COPY_STATUS_SUCCESS` | String copied successfully. |
| `STRING_COPY_STATUS_INVALID_ARGUMENT` | One or more input arguments are invalid. |
| `STRING_COPY_STATUS_BUFFER_TOO_SMALL` | Destination buffer cannot contain the complete string including `'\0'`. |

---

## Design Decisions

### Destination buffer size

The destination capacity is explicitly provided through:

```c
uint32_t dest_size
```

The implementation never writes beyond:

```text
dest_size - 1
```

before storing the terminating null character.

### Null terminator

The terminating:

```c
'\0'
```

is always included in a successful copy.

For example:

```text
Source:      h e l l o \0
Destination: h e l l o \0
```

Therefore, copying `"hello"` requires at least six bytes of destination
storage.

### Buffer overflow protection

If the destination buffer is too small, the function returns:

```text
STRING_COPY_STATUS_BUFFER_TOO_SMALL
```

instead of writing beyond the destination boundary.

For example:

```text
Destination capacity: 5
Source:              "hello"
```

The source requires six bytes including `'\0'`, so the operation fails.

### Read-only source

The source pointer is declared as:

```c
const char * const src
```

The function only reads the source string and does not modify it.

### Empty strings

An empty string:

```text
""
```

contains only the null terminator.

Therefore, a destination buffer with capacity `1U` is sufficient to copy an
empty string successfully.

### Defensive programming

The implementation validates:

- `dest != NULL`
- `src != NULL`
- `dest_size != 0U`

Invalid arguments return:

```text
STRING_COPY_STATUS_INVALID_ARGUMENT
```

before memory access occurs.

### No dynamic memory allocation

The implementation does not allocate or release memory.

Memory usage is deterministic and limited to local variables.

---

## Unit Tests

The unit tests verify:

- Normal string copy.
- Empty string copy.
- Destination buffer exactly large enough.
- Destination buffer too small.
- One-byte destination buffer with an empty string.
- One-byte destination buffer with a non-empty string.
- `NULL` destination pointer.
- `NULL` source pointer.
- Zero destination buffer size.

### Test Cases

```text
[01/09] Normal string copy
[02/09] Empty string
[03/09] Exact buffer size
[04/09] Buffer too small
[05/09] One byte buffer
[06/09] One byte buffer too small
[07/09] Null destination
[08/09] Null source
[09/09] Zero destination size
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
make string_copy_test
```

The build produces:

```text
string_copy_test
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
Running string_copy unit tests
========================================
[01/09] Normal string copy           [PASS]
[02/09] Empty string                [PASS]
[03/09] Exact buffer size            [PASS]
[04/09] Buffer too small             [PASS]
[05/09] One byte buffer              [PASS]
[06/09] One byte buffer too small    [PASS]
[07/09] Null destination             [PASS]
[08/09] Null source                 [PASS]
[09/09] Zero destination size        [PASS]
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
| `make string_copy_test` | Build the project explicitly. |
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
string_copy.o
string_copy_test.o
string_copy_test
```

---

## Concepts Practiced

- String copying
- Null-terminated strings
- Character-by-character traversal
- Destination buffer management
- Buffer overflow prevention
- Null terminator handling
- Pointer validation
- `const` correctness
- Fixed-width integer types
- Defensive programming
- Explicit status reporting
- Static memory usage
- Unit testing
- Makefile
- Embedded C coding practices