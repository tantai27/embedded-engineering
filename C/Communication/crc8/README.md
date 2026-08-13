# CRC-8

## Overview

This module implements a CRC-8 checksum calculation for a byte array.

The exercise focuses on implementing a common data-integrity mechanism used in
embedded communication systems to detect accidental data corruption during
transmission or storage.

The implementation uses the CRC-8/ITU algorithm with the following parameters:

- Polynomial: `0x07`
- Initial value: `0x00`
- Input reflection: Disabled
- Output reflection: Disabled
- Final XOR value: `0x00`

The implementation is expected to:

- Calculate a CRC-8 value from an input byte array.
- Process the input data byte by byte and bit by bit.
- Validate input pointers before accessing memory.
- Keep the input data read-only.
- Return an explicit status code.
- Store the calculated CRC through an output pointer.
- Use fixed-width integer types suitable for embedded systems.
- Follow defensive programming and clean Embedded C coding practices.
- Avoid dynamic memory allocation.

The module should provide a small, reusable API suitable for communication
software and other embedded applications requiring basic data-integrity
verification.

---

## Project Structure

```text
crc8/
├── Makefile
├── README.md
├── crc8.c
├── crc8.h
└── crc8_test.c
```

| File          | Description                                           |
|---------------|-------------------------------------------------------|
| `crc8.h`      | Public API and CRC-8 status definitions.             |
| `crc8.c`      | CRC-8 calculation implementation.                    |
| `crc8_test.c` | Unit tests for the CRC-8 implementation.             |
| `Makefile`    | Build, run and clean targets.                         |
| `README.md`   | Module documentation and test information.            |

---

## API

```c
crc8_status_t crc8_calculate(const uint8_t * const data,
                             uint32_t length,
                             uint8_t * const out_crc);
```

### Parameters

| Parameter | Description |
|-----------|-------------|
| `data` | Pointer to the input byte array. |
| `length` | Number of bytes to process. |
| `out_crc` | Pointer to store the calculated CRC-8 value. |

### Return Status

| Status | Description |
|--------|-------------|
| `CRC8_STATUS_SUCCESS` | CRC calculation completed successfully. |
| `CRC8_STATUS_INVALID_ARGUMENT` | One or more input arguments are invalid. |

---

## CRC Configuration

The implementation uses the following CRC parameters:

| Parameter | Value |
|-----------|-------|
| Width | `8` bits |
| Polynomial | `0x07` |
| Initial value | `0x00` |
| Input reflection | Disabled |
| Output reflection | Disabled |
| Final XOR | `0x00` |

These parameters define the exact CRC configuration implemented by this
module.

The configuration is kept explicit so that the algorithm can be reproduced
and verified using known test vectors.

---

## Algorithm

The CRC is calculated by processing every input byte and then processing each
bit within that byte.

For every input byte:

1. XOR the input byte with the current CRC value.
2. Process all 8 bits of the byte.
3. Check the most significant bit of the current CRC value.
4. Shift the CRC left by one bit.
5. Apply the polynomial `0x07` when the most significant bit was set.
6. Continue with the next bit.
7. Continue with the next input byte.

The core operation can be represented conceptually as:

```text
if (MSB == 1)
{
    CRC = (CRC << 1) XOR 0x07
}
else
{
    CRC = CRC << 1
}
```

The implementation processes the input buffer directly and does not require
an additional buffer.

---

## Design Decisions

### Read-only input

The input data is declared as:

```c
const uint8_t * const data
```

The CRC calculation must not modify the caller's input buffer.

This is important when the input represents a communication frame, protocol
packet or memory region that may be shared with other software components.

### Explicit output pointer

The calculated CRC is returned through:

```c
uint8_t * const out_crc
```

This allows the function to return both the execution status and the
calculated CRC value.

The output value is written only after successful processing.

### Defensive programming

The function validates its pointer arguments before accessing memory:

```c
if ((NULL == data) || (NULL == out_crc))
```

Invalid arguments result in:

```text
CRC8_STATUS_INVALID_ARGUMENT
```

rather than an invalid memory access.

### No dynamic memory allocation

The algorithm processes the input buffer directly.

No heap allocation is required, making the implementation suitable for
embedded systems where deterministic memory usage is preferred.

### Fixed-width integer types

The implementation uses:

- `uint8_t` for input bytes and CRC state.
- `uint32_t` for the input length.

This makes the intended data widths explicit and avoids depending on the
implementation-defined size of basic integer types.

### Bitwise implementation

The CRC is intentionally implemented using bitwise operations rather than a
lookup table.

This keeps the algorithm easy to inspect and understand while practicing:

- XOR operations.
- Bit shifting.
- MSB detection.
- Polynomial processing.

A table-driven implementation could be considered later when optimizing for
execution speed.

---

## Unit Tests

The unit tests use a table-driven structure to execute multiple independent
test cases and provide a consistent execution summary.

The following scenarios are verified:

- Known CRC test vector.
- Single zero byte.
- Single non-zero byte.
- Multiple input bytes.
- Empty input.
- NULL input pointer.
- NULL output pointer.

### Known Test Vector

The implementation is verified using:

```text
Input : 123456789
CRC   : 0xF4
```

The expected CRC value corresponds to the exact CRC configuration implemented
by this module.

### Single-byte tests

A single zero byte is tested separately from a non-zero byte.

This verifies that the implementation handles the initial CRC state and
individual bit transitions correctly.

### Multiple-byte test

Multiple input bytes are processed to verify that the CRC state is correctly
carried from one byte to the next.

### Empty input

A zero-length input is tested to verify the behavior when no data bytes are
processed.

The CRC remains at the configured initial value.

### Invalid argument tests

The following invalid inputs are tested:

- NULL input data pointer.
- NULL output pointer.

These tests verify the defensive programming behavior of the API.

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

or:

```bash
make crc8
```

The build produces:

```text
crc8_test
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
Running crc8 unit tests
========================================
[01/07] Known CRC vector              [PASS]
[02/07] Single zero byte             [PASS]
[03/07] Single byte                  [PASS]
[04/07] Multiple bytes               [PASS]
[05/07] Empty input                  [PASS]
[06/07] Null data pointer            [PASS]
[07/07] Null output pointer          [PASS]
----------------------------------------
Summary
----------------------------------------
Executed : 7/7
Passed   : 7/7 (100%)
Failed   : 0/7 (0%)
========================================
```

A successful test run returns `EXIT_SUCCESS`.

If any test fails, the test application returns `EXIT_FAILURE`.

This makes the test executable suitable for later integration into an
automated build or CI pipeline.

---

## Makefile Targets

| Target | Description |
|--------|-------------|
| `make` | Build the CRC-8 unit test executable. |
| `make crc8` | Build the project explicitly. |
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
crc8.o
crc8_test.o
crc8_test
```

---

## Concepts Practiced

- CRC-based error detection
- Polynomial-based checksum calculation
- CRC configuration parameters
- Bitwise XOR (`^`)
- Left shift (`<<`)
- Most-significant-bit detection
- Fixed-width integer types
- `const` pointer usage
- Defensive programming
- Input validation
- Explicit status reporting
- Table-driven unit testing
- Embedded communication concepts
- Static memory usage
- Makefile