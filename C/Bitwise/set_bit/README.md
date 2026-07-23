# Set Bit

## Overview

This module provides a simple API to set a specific bit in a 32-bit register.

The implementation follows common Embedded C practices:

- Defensive programming
- Input validation
- Clean API design
- Unit testing
- MISRA-friendly coding style

---

## Project Structure

```
set_bit/
├── Makefile
├── README.md
├── set_bit.c
├── set_bit.h
└── set_bit_test.c
```

| File | Description |
|------|-------------|
| `set_bit.h` | Public API declaration. |
| `set_bit.c` | Function implementation. |
| `set_bit_test.c` | Unit tests. |
| `Makefile` | Build, run and clean targets. |

---

## API

```c
status_t set_bit(volatile uint32_t * const reg,
                 uint8_t pos);
```

### Parameters

| Parameter | Description |
|----------|-------------|
| `reg` | Pointer to the target 32-bit register. |
| `pos` | Bit position in the range `[0, 31]`. |

### Return Value

| Value | Description |
|------|-------------|
| `STATUS_SUCCESS` | Operation completed successfully. |
| `STATUS_INVALID_ARGUMENT` | Invalid pointer or invalid bit position. |

---

## Design Decisions

- Use `volatile` to model memory-mapped registers commonly used in embedded systems.
- Validate all input arguments before modifying the register.
- Prevent undefined behavior by rejecting invalid bit positions.
- Return status codes instead of terminating the program.

---

## Unit Tests

The following scenarios are verified:

- Set bit 0
- Set bit 31
- Set an already-set bit
- Set a bit in a non-zero register
- NULL pointer
- Invalid bit position

---

## Prerequisites

- GCC (C11 or later)
- GNU Make

Verify the tools are available:

```bash
gcc --version
make --version
```

---

## Build

Compile the project:

```bash
make
```

or

```bash
make set_bit
```

---

## Run

Execute all unit tests:

```bash
make run
```

Example output:

```text
========================================
Running set_bit unit tests
========================================
[001/006] Set bit 0                    [PASS]
[002/006] Set bit 31                   [PASS]
[003/006] Set already-set bit          [PASS]
[004/006] Set bit on non-zero register [PASS]
[005/006] Null pointer                 [PASS]
[006/006] Invalid bit position         [PASS]
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

Remove all generated build artifacts:

```bash
make clean
```

---

## Concepts Practiced

- Bitwise OR (`|`)
- Left shift (`<<`)
- Defensive programming
- Input validation
- Undefined behavior prevention
- Integer types (`uint32_t`, `uint8_t`)
- `volatile`
- Basic unit testing
- Makefile