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

The implementation uses externally provided buffers and copies data byte by
byte.

---

## Project Structure

```text
buffer_copy/
├── Makefile
├── README.md
├── buffer_copy.c
├── buffer_copy.h
└── buffer_copy_test.c
```

| File | Description |
|------|-------------|
| `buffer_copy.h` | Public API and buffer copy status definitions. |
| `buffer_copy.c` | Buffer copy implementation and overlap detection. |
| `buffer_copy_test.c` | Unit tests for normal operation, boundaries and invalid arguments. |
| `Makefile` | Build, run and clean targets. |
| `README.md` | Module documentation and test information. |

---

## API

```c
buffer_copy_status_t buffer_copy(
    uint8_t * const destination,
    const uint8_t * const source,
    uint32_t length);
```

### Parameters

| Parameter | Description |
|-----------|-------------|
| `destination` | Pointer to the destination buffer. |
| `source` | Pointer to the source buffer. |
| `length` | Number of bytes to copy. |

The source pointer is declared as `const` because the copy operation must not
modify the source data.

---

## Return Status

| Status | Description |
|--------|-------------|
| `BUFFER_COPY_STATUS_SUCCESS` | Buffer copied successfully. |
| `BUFFER_COPY_STATUS_INVALID_ARGUMENT` | One or more input pointers are invalid. |
| `BUFFER_COPY_STATUS_OVERLAP` | Source and destination buffers overlap. |

---

## Design Decisions

### Byte-by-byte copy

The implementation copies data sequentially:

```text
source[0] -> destination[0]
source[1] -> destination[1]
source[2] -> destination[2]
...
```

This makes the memory operation explicit and easy to inspect during debugging.

### Zero-length operation

A zero-length copy is treated as a successful operation:

```c
buffer_copy(destination, source, 0U);
```

No memory is accessed when `length` is zero.

This follows the principle that there is no data to copy and therefore no
memory access is required.

### Pointer validation

For a non-zero copy operation, both pointers must be valid.

The implementation checks:

```text
destination == NULL
source == NULL
```

before accessing either buffer.

Invalid arguments return:

```text
BUFFER_COPY_STATUS_INVALID_ARGUMENT
```

### Overlap detection

The implementation does not allow the source and destination memory regions
to overlap.

For example:

```text
Buffer:
+----+----+----+----+----+----+
| 10 | 20 | 30 | 40 | 50 | 60 |
+----+----+----+----+----+----+
  ^
  source

     ^
     destination
```

If the requested ranges intersect, the operation returns:

```text
BUFFER_COPY_STATUS_OVERLAP
```

This makes the behavior different from `memmove()`, which is specifically
designed to support overlapping regions.

### No dynamic memory allocation

The module does not use:

```text
malloc()
calloc()
realloc()
free()
```

All memory is provided by the caller.

This keeps memory usage deterministic and suitable for embedded systems.

---

## Unit Tests

The unit tests verify:

- Full-buffer copy.
- Verification of copied data.
- Partial-buffer copy.
- Verification of partial copied data.
- Zero-length copy.
- `NULL` destination.
- `NULL` source.
- Both source and destination being `NULL`.
- Overlapping source and destination buffers.

### Test Cases

```text
[01/09] Copy full buffer
[02/09] Verify full buffer
[03/09] Copy partial buffer
[04/09] Verify partial buffer
[05/09] Zero length copy
[06/09] Null destination
[07/09] Null source
[08/09] Null source and destination
[09/09] Overlapping buffers
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
make buffer_copy_test
```

The build produces:

```text
buffer_copy_test
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
Running buffer_copy unit tests
========================================
[01/09] Copy full buffer             [PASS]
[02/09] Verify full buffer           [PASS]
[03/09] Copy partial buffer          [PASS]
[04/09] Verify partial buffer        [PASS]
[05/09] Zero length copy             [PASS]
[06/09] Null destination             [PASS]
[07/09] Null source                  [PASS]
[08/09] Null source and destination  [PASS]
[09/09] Overlapping buffers          [PASS]
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
| `make buffer_copy_test` | Build the project explicitly. |
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
buffer_copy.o
buffer_copy_test.o
buffer_copy_test
```

---

## Concepts Practiced

- Byte-buffer copying
- Source and destination buffers
- Pointer validation
- `const` correctness
- Zero-length operations
- Memory-region overlap
- Buffer boundaries
- Fixed-width integer types
- `uint8_t`
- `uint32_t`
- Static memory allocation
- Deterministic memory usage
- Defensive programming
- Explicit status reporting
- Unit testing
- Makefile
- Embedded C coding practices