# Clear Bit

## Description

This module provides a simple API to clear a specific bit in a 32-bit register.

The implementation follows common Embedded C practices:

- Defensive programming
- Input validation
- Clean API design
- Unit testing
- MISRA-friendly coding style

---

## Project Structure

```text
clear_bit/
├── Makefile
├── README.md
├── clear_bit.c
├── clear_bit.h
└── clear_bit_test.c
```

| File | Description |
|------|-------------|
| `clear_bit.h` | Public API declaration. |
| `clear_bit.c` | Function implementation. |
| `clear_bit_test.c` | Unit tests. |
| `Makefile` | Build, run and clean targets. |

---

## API

```c
status_t clear_bit(volatile uint32_t * const reg,
                   uint8_t pos);
```

### Parameters

| Parameter | Description |
|-----------|-------------|
| `reg` | Pointer to the target 32-bit register. |
| `pos` | Bit position in the range `[0, 31]`. |

### Return Value

| Value | Description |
|-------|-------------|
| `STATUS_SUCCESS` | Operation completed successfully. |
| `STATUS_INVALID_ARGUMENT` | Invalid pointer or invalid bit position. |

---

## Design Decisions

- Use `volatile` to model memory-mapped registers commonly found in embedded systems.
- Validate all input arguments before modifying the register.
- Prevent undefined behavior by rejecting invalid bit positions.
- Return status codes instead of terminating the program.

---

## Unit Tests

The following scenarios are verified:

- Clear bit 0
- Clear bit 31
- Clear an already-clear bit
- Clear a bit in a non-zero register
- NULL pointer
- Invalid bit position

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
make clear_bit
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
Running clear_bit unit tests
========================================
[01/06] Clear bit 0                     [PASS]
[02/06] Clear bit 31                    [PASS]
[03/06] Clear already-clear bit         [PASS]
[04/06] Clear bit on non-zero register  [PASS]
[05/06] Null pointer                    [PASS]
[06/06] Invalid bit position            [PASS]
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

- Bitwise AND (`&`)
- Bitwise NOT (`~`)
- Left shift (`<<`)
- Defensive programming
- Input validation
- Undefined behavior prevention
- Integer types (`uint32_t`, `uint8_t`)
- `volatile`
- Basic unit testing
- Makefile