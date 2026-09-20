# Parity8

A small Embedded C module for calculating the parity bit of an 8-bit value.

The module supports both even and odd parity and returns the calculated parity bit through an output parameter.

## Overview

Parity is a simple error-detection mechanism commonly used in communication systems.

For an 8-bit data value, the parity bit is selected so that the total number of `1` bits is:

- **Even parity**: even
- **Odd parity**: odd

This module focuses on the parity calculation itself. Communication framing and transmission are outside the scope of this module.

## API

```c
parity8_status_t parity8_calculate(
    uint8_t data,
    parity8_type_t type,
    uint8_t * const parity);
```

### Parameters

| Parameter | Description |
|---|---|
| `data` | 8-bit input value |
| `type` | `PARITY8_EVEN` or `PARITY8_ODD` |
| `parity` | Output pointer receiving the calculated parity bit |

### Return status

| Status | Description |
|---|---|
| `PARITY8_STATUS_SUCCESS` | Parity calculated successfully |
| `PARITY8_STATUS_INVALID_ARGUMENT` | Invalid output pointer or parity type |

## Parity Types

### Even parity

The parity bit is selected so the total number of set bits is even.

Example:

```text
Data:       00000011
Set bits:   2

Even parity bit = 0
Total set bits  = 2
```

### Odd parity

The parity bit is selected so the total number of set bits is odd.

Example:

```text
Data:       00000011
Set bits:   2

Odd parity bit = 1
Total set bits = 3
```

## Design

The implementation calculates parity using XOR operations.

The input is processed one bit at a time:

```text
parity ^= (data & 1U);
data >>= 1U;
```

The resulting value represents whether the input contains an odd or even number of set bits.

For odd parity, the result is inverted.

The implementation does not use dynamic memory allocation.

## Defensive Programming

The module validates:

- Output pointer is not `NULL`.
- Parity type is either `PARITY8_EVEN` or `PARITY8_ODD`.

Invalid arguments return `PARITY8_STATUS_INVALID_ARGUMENT`.

## Scope

This module intentionally focuses only on parity-bit calculation.

It does not implement:

- UART framing
- Serial transmission
- Receive-side parity checking
- Error recovery
- Communication drivers

These responsibilities belong to higher-level communication modules.

## Applications

Parity calculation can be used in communication systems where simple error detection is required, including:

- UART communication
- Serial protocols
- Embedded communication interfaces
- Simple data-integrity checks

## Embedded C Considerations

The implementation demonstrates:

- Fixed-width integer types using `uint8_t`
- Explicit status codes
- Pointer validation
- Bitwise operations
- No dynamic memory allocation
- `const` correctness for output pointer parameters
- Small, deterministic functions

## Complexity

For an 8-bit input, the function processes at most 8 bits.

- **Time complexity:** `O(8)`, effectively `O(1)`
- **Space complexity:** `O(1)`

## Limitations

The module operates on exactly one 8-bit value at a time.

It does not detect all possible transmission errors. For example, an even number of bit errors can preserve the expected parity and therefore remain undetected.

For stronger error detection, checksum or CRC mechanisms may be more appropriate.