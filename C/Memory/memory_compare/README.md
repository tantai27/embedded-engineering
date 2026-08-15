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
├── Makefile
├── README.md
├── memory_compare.c
├── memory_compare.h
└── memory_compare_test.c
```

| File | Description |
|------|-------------|
| `memory_compare.h` | Public API and comparison status definitions. |
| `memory_compare.c` | Byte-by-byte memory comparison implementation. |
| `memory_compare_test.c` | Unit tests for normal, boundary and invalid-argument cases. |
| `Makefile` | Build, run and clean targets. |
| `README.md` | Module documentation and test information. |

---

## API

```c
memory_compare_status_t memory_compare(const void * const lhs,
                                       const void * const rhs,
                                       uint32_t size);
```

### Parameters

| Parameter | Description |
|-----------|-------------|
| `lhs` | Pointer to the first memory region. |
| `rhs` | Pointer to the second memory region. |
| `size` | Number of bytes to compare. |

### Return Status

| Status | Description |
|--------|-------------|
| `MEMORY_COMPARE_STATUS_EQUAL` | The specified memory regions contain identical data. |
| `MEMORY_COMPARE_STATUS_NOT_EQUAL` | The specified memory regions contain different data. |
| `MEMORY_COMPARE_STATUS_INVALID_ARGUMENT` | One or more memory pointers are invalid. |

---

## Design Decisions

### Generic memory interface

The API accepts:

```c
const void * const
```

instead of accepting only `uint8_t *`.

This allows the function to operate on arbitrary memory objects and buffers.

Internally, the memory is accessed as bytes:

```c
const uint8_t *lhs_bytes;
const uint8_t *rhs_bytes;
```

This makes the comparison independent of the original object type.

### Read-only input

Both memory regions are declared as constant pointers to constant data:

```c
const void * const lhs
const void * const rhs
```

The function never modifies either memory region.

This is appropriate for operations such as:

- Comparing received communication data.
- Verifying copied buffers.
- Comparing configuration data.
- Checking memory contents.
- Comparing protocol payloads.

### Explicit comparison length

The function compares exactly `size` bytes.

For example:

```text
lhs:  10 20 30 40
rhs:  10 20 30 40 50
size: 4
```

The result is:

```text
EQUAL
```

because only the first four bytes are part of the requested comparison.

The function does not attempt to determine the actual allocation size of either
memory region.

### Zero-length comparison

A comparison with:

```c
size == 0U
```

is considered successful when both pointers are valid.

No memory is accessed in this case.

This provides deterministic behavior for empty buffers and zero-length data
operations.

### Same-pointer optimization

When both pointers refer to the same memory region:

```c
lhs == rhs
```

the function immediately returns:

```text
MEMORY_COMPARE_STATUS_EQUAL
```

No byte-by-byte comparison is required because a memory region is necessarily
equal to itself for the same requested range.

### Defensive programming

The implementation validates both input pointers before accessing memory.

Invalid input returns:

```text
MEMORY_COMPARE_STATUS_INVALID_ARGUMENT
```

This prevents dereferencing `NULL` pointers.

### No dynamic memory allocation

The implementation does not allocate or release memory.

Memory usage is deterministic and limited to a small number of local variables.

---

## Comparison Behavior

The comparison proceeds sequentially from the first byte to the last requested
byte.

Conceptually:

```text
lhs[0] == rhs[0]
        |
        v
lhs[1] == rhs[1]
        |
        v
      ...
        |
        v
lhs[size - 1] == rhs[size - 1]
```

The function returns immediately when the first different byte is detected.

This avoids unnecessary memory accesses after the comparison result is already
known.

---

## Unit Tests

The unit tests verify:

- Equal memory regions.
- Different data at the last byte.
- Different data at the first byte.
- Comparison using a smaller requested size.
- Same-pointer comparison.
- Zero-length comparison.
- `NULL` first pointer.
- `NULL` second pointer.

### Test Cases

```text
[01/08] Equal memory regions
[02/08] Different last byte
[03/08] Different size ignored
[04/08] Different first byte
[05/08] Same pointer
[06/08] Zero length
[07/08] Null first pointer
[08/08] Null second pointer
```

The `Different size ignored` test verifies an important API property:

```text
data_a = 10 20 30 40
data_d = 10 20 30 40 50
size   = 4
```

Only four bytes are compared, therefore the result is:

```text
MEMORY_COMPARE_STATUS_EQUAL
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
make memory_compare_test
```

The build produces:

```text
memory_compare_test
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
Running memory_compare unit tests
========================================
[01/08] Equal memory regions         [PASS]
[02/08] Different last byte         [PASS]
[03/08] Different size ignored      [PASS]
[04/08] Different first byte        [PASS]
[05/08] Same pointer                [PASS]
[06/08] Zero length                 [PASS]
[07/08] Null first pointer          [PASS]
[08/08] Null second pointer         [PASS]
----------------------------------------
Summary
----------------------------------------
Executed : 8/8
Passed   : 8/8 (100%)
Failed   : 0/8 (0%)
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
| `make memory_compare_test` | Build the project explicitly. |
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
memory_compare.o
memory_compare_test.o
memory_compare_test
```

---

## Concepts Practiced

- Memory comparison
- Byte-level memory access
- `const void *`
- `const uint8_t *`
- Pointer validation
- Pointer equality
- Explicit comparison length
- Zero-length operation
- Early return
- Defensive programming
- Read-only memory access
- Fixed-width integer types
- Static memory usage
- Unit testing
- Makefile
- Embedded buffer handling