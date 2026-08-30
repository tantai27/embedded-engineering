# Checksum-8

## Overview

This module implements an 8-bit additive checksum calculation for a byte
array.

The purpose of the exercise is to practice a simple data-integrity mechanism
commonly used in embedded communication systems to detect accidental data
corruption during transmission or storage.

The checksum is calculated by summing all input bytes and retaining the
least-significant 8 bits of the result.

The implementation uses externally provided input data and does not perform
dynamic memory allocation.

---

## Project Structure

```text
checksum8/
├── Makefile
├── README.md
├── checksum8.c
├── checksum8.h
└── checksum8_test.c
```

| File | Description |
|------|-------------|
| `checksum8.h` | Public API and checksum status definitions. |
| `checksum8.c` | 8-bit additive checksum calculation implementation. |
| `checksum8_test.c` | Unit tests for checksum calculation, overflow and invalid arguments. |
| `Makefile` | Build, run and clean targets. |
| `README.md` | Module documentation and test information. |

---

## API

```c
checksum8_status_t checksum8_calculate(
    const uint8_t * const data,
    uint32_t length,
    uint8_t * const out_checksum);
```

### Parameters

| Parameter | Description |
|-----------|-------------|
| `data` | Pointer to the input byte array. |
| `length` | Number of bytes to process. |
| `out_checksum` | Pointer to store the calculated checksum. |

The input data is declared as `const` because the checksum calculation must
not modify the source buffer.

---

## Return Status

| Status | Description |
|--------|-------------|
| `CHECKSUM8_STATUS_SUCCESS` | Checksum calculation completed successfully. |
| `CHECKSUM8_STATUS_INVALID_ARGUMENT` | One or more input arguments are invalid. |

---

## Checksum Algorithm

The checksum starts at zero and processes each byte sequentially.

For input data:

```text
01 02 03 04
```

the calculation is:

```text
checksum = 0
checksum = 0 + 0x01
checksum = 1 + 0x02
checksum = 3 + 0x03
checksum = 6 + 0x04

checksum = 0x0A
```

The final value is stored through the output pointer.

---

## Overflow Handling

The checksum is stored in a `uint8_t`.

When the accumulated value exceeds `0xFF`, the result wraps around to the
least-significant 8 bits.

For example:

```text
0xFF + 0x01 = 0x100
```

After conversion to `uint8_t`:

```text
0x100 -> 0x00
```

Therefore:

```text
Input:
FF 01

Checksum:
00
```

This behavior is intentional and defines the 8-bit checksum calculation.

---

## Design Decisions

### Byte-by-byte processing

The implementation processes the input buffer sequentially:

```text
data[0]
data[1]
data[2]
...
data[length - 1]
```

This keeps the algorithm simple, deterministic and easy to inspect.

### Explicit output parameter

The calculated checksum is returned through an output pointer rather than
using the function return value.

The return value is reserved for operation status:

```text
status
    |
    +-- SUCCESS
    |
    +-- INVALID_ARGUMENT
```

This separates the calculated result from error handling.

### Input data remains read-only

The source pointer is declared as:

```c
const uint8_t * const data
```

This communicates that the checksum function does not modify the input buffer.

### Pointer validation

The implementation validates:

```text
data == NULL
out_checksum == NULL
```

before accessing the buffers.

Invalid arguments return:

```text
CHECKSUM8_STATUS_INVALID_ARGUMENT
```

### Zero-length input

A zero-length input is valid as long as both pointers are valid.

For example:

```c
uint8_t checksum = 0U;

checksum8_calculate(data,
                    0U,
                    &checksum);
```

No input bytes are processed and the checksum remains:

```text
0x00
```

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

- Basic checksum calculation.
- Correct checksum result.
- 8-bit checksum overflow.
- Correct result after overflow.
- Single-byte input.
- `NULL` input data pointer.
- `NULL` output pointer.
- Both pointers being `NULL`.

### Test Cases

```text
[01/08] Basic checksum
[02/08] Basic checksum value
[03/08] Checksum overflow
[04/08] Overflow checksum value
[05/08] Single byte checksum
[06/08] Null data pointer
[07/08] Null output pointer
[08/08] Null pointers
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
make checksum8_test
```

The build produces:

```text
checksum8_test
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
Running checksum8 unit tests
========================================
[01/08] Basic checksum               [PASS]
[02/08] Basic checksum value         [PASS]
[03/08] Checksum overflow            [PASS]
[04/08] Overflow checksum value      [PASS]
[05/08] Single byte checksum         [PASS]
[06/08] Null data pointer            [PASS]
[07/08] Null output pointer          [PASS]
[08/08] Null pointers                [PASS]
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

---

## Makefile Targets

| Target | Description |
|--------|-------------|
| `make` | Build the unit test executable. |
| `make checksum8_test` | Build the project explicitly. |
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
checksum8.o
checksum8_test.o
checksum8_test
```

---

## Concepts Practiced

- Additive checksum
- Data integrity
- Byte-array processing
- 8-bit arithmetic
- Unsigned integer overflow
- `uint8_t`
- `uint32_t`
- `const` correctness
- Pointer validation
- Output parameters
- Zero-length input
- Static memory usage
- Deterministic behavior
- Defensive programming
- Explicit status reporting
- Unit testing
- Makefile
- Embedded communication concepts
- Embedded C coding practices