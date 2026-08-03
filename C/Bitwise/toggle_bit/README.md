# Toggle Bit

## Description

This module provides a simple API to toggle a specific bit in a 32-bit register.

The implementation follows common Embedded C practices:

- Defensive programming
- Input validation
- Clean API design
- Unit testing
- MISRA-friendly coding style

---

## Project Structure

```text
toggle_bit/
├── Makefile
├── README.md
├── toggle_bit.c
├── toggle_bit.h
└── toggle_bit_test.c
```

| File | Description |
|------|-------------|
| `toggle_bit.h` | Public API declaration. |
| `toggle_bit.c` | Function implementation. |
| `toggle_bit_test.c` | Unit tests. |
| `Makefile` | Build, run and clean targets. |

---

## API

```c
status_t toggle_bit(volatile uint32_t * const reg,
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

- Toggle bit 0
- Toggle bit 31
- Toggle an already-set bit
- Toggle an already-clear bit
- Toggle a bit in a non-zero register
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
make toggle_bit
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
Running toggle_bit unit tests
========================================
[01/07] Toggle bit 0                     [PASS]
[02/07] Toggle bit 31                    [PASS]
[03/07] Toggle already-set bit           [PASS]
[04/07] Toggle already-clear bit         [PASS]
[05/07] Toggle bit on non-zero register  [PASS]
[06/07] Null pointer                     [PASS]
[07/07] Invalid bit position             [PASS]
----------------------------------------
Summary
----------------------------------------
Executed : 7/7
Passed   : 7/7 (100%)
Failed   : 0/7 (0%)
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

- Bitwise XOR (`^`)
- Left shift (`<<`)
- Defensive programming
- Input validation
- Undefined behavior prevention
- Integer types (`uint32_t`, `uint8_t`)
- `volatile`
- Basic unit testing
- Makefile