# CRC-16

## Overview

This module implements a CRC-16 checksum calculation for a byte array.

The purpose of the exercise is to practice a commonly used data-integrity
mechanism in embedded communication systems and extend the CRC knowledge
introduced by the CRC-8 module.

The implementation uses the CRC-16/IBM algorithm with the following parameters:

- Polynomial: `0x8005`
- Initial value: `0x0000`
- Input reflection: Enabled
- Output reflection: Enabled
- Final XOR value: `0x0000`

The reflected implementation uses the reversed polynomial:

```text
0xA001
```

The implementation is expected to:

- Calculate a CRC-16 value from an input byte array.
- Process the input data byte by byte and bit by bit.
- Validate input pointers before accessing memory.
- Keep the input data read-only.
- Store the calculated CRC through an output pointer.
- Return an explicit status code.
- Use fixed-width integer types suitable for embedded systems.
- Avoid dynamic memory allocation.
- Follow defensive programming and clean Embedded C coding practices.

The module should provide a small, reusable API suitable for communication
software, protocol payloads and other embedded applications requiring
data-integrity verification.

---

## Project Structure

```text
crc16/
├── Makefile
├── README.md
├── crc16.c
├── crc16.h
└── crc16_test.c
```

| File | Description |
|------|-------------|
| `crc16.h` | Public API and CRC-16 status definitions. |
| `crc16.c` | CRC-16/IBM calculation implementation. |
| `crc16_test.c` | Unit tests for CRC calculation and invalid arguments. |
| `Makefile` | Build, run and clean targets. |
| `README.md` | Module documentation and test information. |

---

## API

```c
crc16_status_t crc16_calculate(const uint8_t * const data,
                               uint32_t length,
                               uint16_t * const out_crc);
```

### Parameters

| Parameter | Description |
|-----------|-------------|
| `data` | Pointer to the input byte array. |
| `length` | Number of bytes to process. |
| `out_crc` | Pointer to store the calculated CRC-16 value. |

### Return Status

| Status | Description |
|--------|-------------|
| `CRC16_STATUS_SUCCESS` | CRC calculation completed successfully. |
| `CRC16_STATUS_INVALID_ARGUMENT` | One or more input arguments are invalid. |

---

## CRC-16/IBM Parameters

| Parameter | Value |
|-----------|-------|
| Width | 16 bits |
| Polynomial | `0x8005` |
| Initial value | `0x0000` |
| Input reflection | Enabled |
| Output reflection | Enabled |
| Final XOR | `0x0000` |

Because input and output reflection are enabled, the implementation processes
the least-significant bit first and uses the reversed polynomial:

```text
0xA001
```

---

## Design Decisions

### Byte-by-byte processing

The input is processed one byte at a time.

Each byte is XORed into the current CRC state before the individual bits are
processed.

### Bit-by-bit processing

Each input byte contains eight bits.

For every bit, the least-significant CRC bit is checked:

```text
CRC bit 0 == 1
```

If set, the CRC is shifted and XORed with the reversed polynomial.

Otherwise, the CRC is only shifted.

### Fixed initial value

The CRC state starts with:

```text
0x0000
```

This provides deterministic behavior for every calculation.

### Zero-length input

A zero-length input is valid when the data pointer and output pointer are
valid.

No input bytes are processed and the resulting CRC remains:

```text
0x0000
```

### Read-only input

The input data is declared as:

```c
const uint8_t * const data
```

The implementation does not modify the input buffer.

### Defensive programming

The implementation validates:

- `data != NULL`
- `out_crc != NULL`

Invalid arguments return:

```text
CRC16_STATUS_INVALID_ARGUMENT
```

before accessing memory.

### No dynamic memory allocation

The implementation does not allocate or release memory.

Memory usage is deterministic and limited to local variables.

---

## Known Test Vector

The standard CRC-16/IBM test vector:

```text
Input:
"123456789"
```

produces:

```text
CRC = 0xBB3D
```

This vector is used by the unit tests to verify the core CRC implementation.

---

## Unit Tests

The unit tests verify:

- Standard CRC-16/IBM known vector.
- Single zero byte.
- Binary data.
- Zero-length input.
- `NULL` input pointer.
- `NULL` output pointer.
- Both input and output pointers being `NULL`.
- Zero-length input with valid pointers.

### Test Cases

```text
[01/08] CRC-16/IBM known vector
[02/08] Single zero byte
[03/08] Binary data
[04/08] Zero length
[05/08] Null data pointer
[06/08] Null output pointer
[07/08] Null data and output
[08/08] Empty data with valid output
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
make crc16_test
```

The build produces:

```text
crc16_test
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
Running crc16 unit tests
========================================
[01/08] CRC-16/IBM known vector       [PASS]
[02/08] Single zero byte              [PASS]
[03/08] Binary data                   [PASS]
[04/08] Zero length                   [PASS]
[05/08] Null data pointer             [PASS]
[06/08] Null output pointer           [PASS]
[07/08] Null data and output          [PASS]
[08/08] Empty data with valid output  [PASS]
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
| `make crc16_test` | Build the project explicitly. |
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
crc16.o
crc16_test.o
crc16_test
```

---

## Concepts Practiced

- CRC-16
- CRC-16/IBM
- Polynomial-based checksum
- Bitwise operations
- Bit shifting
- XOR operations
- Reflected CRC processing
- Byte-by-byte processing
- Bit-by-bit processing
- Pointer validation
- `const` correctness
- Fixed-width integer types
- Defensive programming
- Explicit status reporting
- Static memory usage
- Communication data integrity
- Unit testing
- Makefile
- Embedded C coding practices