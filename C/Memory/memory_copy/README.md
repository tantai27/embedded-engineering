# Memory Copy

## Description

This module implements a safe API to copy a memory block from a source buffer to a destination buffer.

The implementation is designed following common Embedded C and Automotive software practices, with emphasis on robustness, defensive programming and predictable behavior.

The implementation is expected to:

- Copy an arbitrary number of bytes from the source buffer to the destination buffer.
- Validate all input arguments before accessing memory.
- Safely handle overlapping memory regions.
- Preserve source data integrity throughout the copy operation.
- Provide a simple, reusable API with explicit status reporting.

---

## Project Structure

```text
memory_copy/
├── Makefile
├── README.md
├── memory_copy.c
├── memory_copy.h
└── memory_copy_test.c
```

| File | Description |
|------|-------------|
| `memory_copy.h` | Public API declaration. |
| `memory_copy.c` | Function implementation. |
| `memory_copy_test.c` | Unit tests. |
| `Makefile` | Build, run and clean targets. |

---

## API

```c
mem_status_t memory_copy(void * const dest,
                         const void * const src,
                         size_t length);
```

### Parameters

| Parameter | Description |
|-----------|-------------|
| `dest` | Pointer to the destination buffer. |
| `src` | Pointer to the source buffer. |
| `length` | Number of bytes to copy. |

### Return Value

| Value | Description |
|-------|-------------|
| `MEM_STATUS_SUCCESS` | Copy completed successfully. |
| `MEM_STATUS_INVALID_ARGUMENT` | Invalid input pointer. |

---

## Design Decisions

- Use `uint8_t` pointers to perform byte-wise memory copy.
- Validate all input pointers before accessing memory.
- Safely support overlapping memory regions by selecting forward or backward copy direction.
- Use `size_t` for memory length, matching the C standard library interface.
- Return explicit status codes instead of terminating the program.

---

## Unit Tests

The following scenarios are verified:

- Copy a normal memory block.
- Copy zero bytes.
- Copy overlapping memory (forward).
- Copy overlapping memory (backward).
- NULL destination pointer.
- NULL source pointer.

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

Build the project:

```bash
make
```

or

```bash
make memory_copy
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
Running memory_copy unit tests
========================================
[01/06] Copy normal buffer             [PASS]
[02/06] Copy zero length               [PASS]
[03/06] Overlap forward copy           [PASS]
[04/06] Overlap backward copy          [PASS]
[05/06] Null destination               [PASS]
[06/06] Null source                    [PASS]
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

Remove generated build artifacts:

```bash
make clean
```

---

## Concepts Practiced

- Pointer arithmetic
- Memory copy
- Overlapping memory handling
- Defensive programming
- Input validation
- Integer types (`uint8_t`, `size_t`)
- Basic unit testing
- Makefile