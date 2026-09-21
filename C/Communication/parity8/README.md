# Parity8

## Overview

`parity8` is a small Embedded C module for calculating the parity bit of an 8-bit data value.

The module supports:

- Even parity
- Odd parity
- Input validation
- Explicit status codes
- No dynamic memory allocation
- Deterministic execution

The implementation is designed as a reusable low-level communication utility that can be used as part of UART, serial communication, framing, or data-integrity logic.

---

## Problem Statement

Parity is a simple error-detection mechanism commonly used in serial communication.

For an 8-bit data value, the parity bit is selected so that the total number of set bits satisfies the selected parity rule:

- **Even parity**: total number of `1` bits is even.
- **Odd parity**: total number of `1` bits is odd.

For example, the value `0x03` contains two set bits:

```text
0x03 = 0000 0011
          ^^
```

Therefore:

- Even parity bit = `0`
- Odd parity bit = `1`

The `parity8` module calculates this parity bit from the input data.

---

## Features

- Calculate even parity.
- Calculate odd parity.
- Detect invalid output pointers.
- Detect invalid parity types.
- Return explicit status codes.
- Use fixed-width integer types.
- No dynamic memory allocation.
- Suitable for embedded and bare-metal environments.

---

## API

### `parity8_calculate()`

```c
parity8_status_t parity8_calculate(
    uint8_t data,
    parity8_type_t type,
    uint8_t * const parity);
```

Calculates the parity bit required for the specified parity type.

### Parameters

| Parameter | Type | Description |
|---|---|---|
| `data` | `uint8_t` | 8-bit input data |
| `type` | `parity8_type_t` | Requested parity type |
| `parity` | `uint8_t *` | Output pointer for the calculated parity bit |

The output value is always either:

- `0U`
- `1U`

### Return values

| Status | Meaning |
|---|---|
| `PARITY8_STATUS_SUCCESS` | Parity calculation completed successfully |
| `PARITY8_STATUS_INVALID_ARGUMENT` | Invalid output pointer or parity type |

---

## Parity Types

The module defines:

```c
typedef enum
{
    PARITY8_EVEN = 0U,
    PARITY8_ODD
} parity8_type_t;
```

### Even parity

The parity bit is selected so the total number of set bits is even.

Example:

```text
Data:        0000 0011
Set bits:          2
Even parity:      0
Total:             2
```

### Odd parity

The parity bit is selected so the total number of set bits is odd.

Example:

```text
Data:        0000 0011
Set bits:          2
Odd parity:       1
Total:             3
```

---

## Implementation

The implementation calculates parity using XOR of the individual bits.

Conceptually:

```text
parity = bit0 XOR bit1 XOR ... XOR bit7
```

The input value is shifted right until all bits have been processed.

For even parity:

```text
parity = number_of_set_bits mod 2
```

For odd parity, the result is inverted:

```text
parity = NOT(number_of_set_bits mod 2)
```

The implementation does not need to explicitly count the number of set bits.

---

## Defensive Programming

The API validates all externally supplied arguments.

Invalid conditions include:

- `parity == NULL`
- Invalid `parity8_type_t` value

Example:

```c
uint8_t parity = 0U;

parity8_calculate(
    0x55U,
    PARITY8_EVEN,
    &parity);
```

For an invalid output pointer:

```c
parity8_calculate(
    0x55U,
    PARITY8_EVEN,
    NULL);
```

the function returns:

```c
PARITY8_STATUS_INVALID_ARGUMENT
```

No output memory is accessed when the argument is invalid.

---

## Unit Tests

The module contains 10 unit tests.

| # | Test | Purpose |
|---|---|---|
| 1 | Even parity zero | Verify `0x00` with even parity |
| 2 | Even parity all ones | Verify `0xFF` with even parity |
| 3 | Even parity odd set bits | Verify odd number of set bits |
| 4 | Even parity even set bits | Verify even number of set bits |
| 5 | Odd parity odd set bits | Verify odd parity with odd set-bit count |
| 6 | Odd parity even set bits | Verify odd parity with even set-bit count |
| 7 | Even parity alternating bits | Verify `0xAA` |
| 8 | Odd parity alternating bits | Verify `0x55` |
| 9 | Null output pointer | Verify defensive argument validation |
| 10 | Invalid parity type | Verify invalid enum handling |

The test suite also verifies both parity modes using values with different numbers and patterns of set bits.

### Expected result

```text
========================================
Running parity8 unit tests
========================================
[01/10] Even parity zero             [PASS]
[02/10] Even parity all ones        [PASS]
[03/10] Even parity odd set bits    [PASS]
[04/10] Even parity even set bits   [PASS]
[05/10] Odd parity odd set bits     [PASS]
[06/10] Odd parity even set bits    [PASS]
[07/10] Even parity alternating bits [PASS]
[08/10] Odd parity alternating bits  [PASS]
[09/10] Null output pointer          [PASS]
[10/10] Invalid parity type          [PASS]
----------------------------------------
Summary
----------------------------------------
Executed : 10/10
Passed   : 10/10 (100%)
Failed   : 0/10 (0%)
========================================
```

---

## Build

The project uses GCC and a simple Makefile.

### Build

```bash
make
```

This creates:

```text
parity8_test
```

### Run tests

```bash
make run
```

### Clean

```bash
make clean
```

This removes generated object files and the test executable.

---

## Project Structure

```text
parity8/
├── parity8.c
├── parity8.h
├── parity8_test.c
├── Makefile
└── README.md
```

---

## Build Configuration

The project is compiled with:

```text
-std=c11
-Wall
-Wextra
-Wpedantic
```

These options help detect common implementation mistakes and keep the code aligned with a strict C development style.

---

## Embedded C Considerations

The implementation intentionally uses:

- `uint8_t` for 8-bit data.
- Explicit enumerations for parity modes.
- Explicit status codes instead of relying on implicit error handling.
- Pointer validation before dereferencing.
- No dynamic memory allocation.
- Deterministic control flow.
- No global mutable state.
- No recursion.

These characteristics make the module suitable for integration into larger embedded communication software.

---

## Error Detection Capability

Parity provides only limited error detection.

For a single-bit error:

```text
Original:  1010 0010
Received:  1010 0000
```

the number of set bits changes, so the parity check can detect the error.

However, parity cannot detect every type of corruption.

For example, an even number of bit errors can preserve the original parity:

```text
Original:  1010 0010
Received:  1000 0000
```

Two bits changed, but the parity relationship may remain valid.

Therefore, parity should not be considered a complete data-integrity mechanism.

For stronger error detection, protocols may use:

- Checksum
- CRC
- Frame validation
- Sequence counters
- Higher-level integrity mechanisms

---

## Applications

The module can be used as a building block for:

- UART communication
- Serial communication
- Communication frame generation
- Communication frame validation
- Simple error-detection mechanisms
- Embedded communication drivers

For example, a UART transmitter can calculate the parity bit after preparing the data byte and append it to the transmitted frame.

---

## Complexity

For an 8-bit input, the implementation processes at most 8 bits.

Therefore:

```text
Time complexity:  O(8) ≈ O(1)
Space complexity: O(1)
```

No additional memory proportional to the input size is required.

---

## Limitations

This module intentionally focuses only on calculating the parity bit.

It does not implement:

- UART framing
- Start/stop bits
- Baud-rate generation
- Serial transmission
- Serial reception
- Parity checking against a received frame
- Error counters
- Retry mechanisms
- CRC/checksum algorithms

These responsibilities belong to higher-level communication modules.

---

## Related Communication Concepts

This module provides practice with several Embedded C and communication concepts:

- Bit manipulation
- XOR operations
- Bit shifting
- Fixed-width integer types
- Enumeration-based APIs
- Pointer validation
- Defensive programming
- Error/status handling
- Simple error-detection mechanisms
- Unit testing
- Make-based build automation

---

## Design Goals

The main design goals are:

1. Keep the API small.
2. Make invalid input handling explicit.
3. Avoid dynamic allocation.
4. Keep execution deterministic.
5. Make the implementation easy to test.
6. Keep the module reusable in embedded communication code.
7. Keep the implementation simple enough to integrate into a larger driver.

---

## Scope

This module is intentionally small.

The goal is not to implement a complete communication stack, but to provide a focused and reusable parity calculation primitive that can be integrated into larger embedded communication components.