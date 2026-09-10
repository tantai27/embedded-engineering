# Bit Extract

A lightweight Embedded C module for extracting a contiguous bit field from a 32-bit unsigned value.

The module extracts a specified number of bits starting at a given bit position and places the extracted field in the least significant bits of the result.

## Features

- Extract a contiguous bit field from a `uint32_t` value.
- Support arbitrary valid bit positions and widths.
- Validate extraction boundaries.
- Use fixed-width integer types.
- No dynamic memory allocation.
- Hardware-independent implementation.
- Deterministic execution.
- Explicit status reporting for invalid arguments.

## API

### `bit_extract()`

```c
bit_extract_status_t bit_extract(
    uint32_t value,
    uint8_t position,
    uint8_t width,
    uint32_t * const result);
```

Extracts `width` bits from `value`, starting at `position`.

Bit position `0` represents the least significant bit.

The extracted field is right-aligned in `result`.

For example:

```text
value:
1011 0100 1101 0010 0001 1010 0110 1111
                         ^^^^^^^^
                         bit field
```

If the selected field contains:

```text
1010 0110
```

the returned result is:

```text
0000 0000 0000 0000 0000 0000 1010 0110
```

## Status

The module returns a status value indicating whether the operation completed successfully.

```c
typedef enum
{
    BIT_EXTRACT_STATUS_SUCCESS = 0U,
    BIT_EXTRACT_STATUS_INVALID_ARGUMENT
} bit_extract_status_t;
```

### `BIT_EXTRACT_STATUS_SUCCESS`

The bit field was extracted successfully.

### `BIT_EXTRACT_STATUS_INVALID_ARGUMENT`

Returned when one or more arguments are invalid.

Invalid conditions include:

- `result == NULL`
- `position >= 32`
- `width == 0`
- `position + width > 32`

## Bit Position and Width

The valid bit positions of the input value are:

```text
31 .............................. 0
MSB                              LSB
```

The extraction range is defined by:

```text
position
    ↓
    [----------------]
    width bits
```

The highest accessed bit is:

```text
position + width - 1
```

Therefore, a valid extraction must satisfy:

```text
position + width <= 32
```

Examples:

| Position | Width | Valid | Description |
|---:|---:|:---:|---|
| `0` | `1` | Yes | Extract bit 0 |
| `0` | `8` | Yes | Extract bits 0–7 |
| `8` | `8` | Yes | Extract bits 8–15 |
| `24` | `8` | Yes | Extract bits 24–31 |
| `0` | `32` | Yes | Extract the complete value |
| `31` | `1` | Yes | Extract bit 31 |
| `32` | `1` | No | Position outside the value |
| `28` | `5` | No | Requested field exceeds bit 31 |
| `0` | `0` | No | Zero-width extraction |

## Implementation

The implementation first validates the requested extraction range.

For a valid width smaller than 32 bits, a mask containing `width` set bits is generated:

```text
width = 5

mask = 0000 0000 0000 0000 0000 0000 0001 1111
```

The input value is then shifted right by `position`:

```text
value >> position
```

and the resulting value is masked:

```text
(value >> position) & mask
```

This moves the requested bit field into the least significant bits while clearing all other bits.

For a full-width extraction (`width == 32`), `UINT32_MAX` is used directly as the mask.

This avoids performing a shift by the complete width of the value.

## Example

Given:

```text
value = 0xABCD1234
```

and:

```text
position = 8
width = 8
```

the input can be represented as:

```text
0xABCD1234
    ↓
    0x12
```

The selected bits are bits 8 through 15:

```text
1010 1011 1100 1101 0001 0010 0011 0100
                 ^^^^^^^^
```

After shifting and masking, the result is:

```text
0x00000012
```

Example usage:

```c
#include <stdint.h>
#include <stdio.h>

#include "bit_extract.h"

int main(void)
{
    uint32_t value = 0xABCD1234UL;
    uint32_t field = 0U;

    if (BIT_EXTRACT_STATUS_SUCCESS ==
        bit_extract(value, 8U, 8U, &field))
    {
        printf("Extracted field: 0x%08X\n", field);
    }

    return 0;
}
```

## Boundary Handling

Boundary conditions are explicitly handled to make the module safe for low-level use.

### Zero Width

A zero-width extraction is rejected:

```c
bit_extract(value, 0U, 0U, &result);
```

returns:

```text
BIT_EXTRACT_STATUS_INVALID_ARGUMENT
```

### Invalid Position

A 32-bit value has bit positions `0` through `31`.

Therefore:

```c
bit_extract(value, 32U, 1U, &result);
```

is invalid.

### Field Exceeds Value Width

An extraction beginning at bit 28 with width 5 would require bits:

```text
28, 29, 30, 31, 32
```

Bit 32 does not exist in a 32-bit value, so:

```c
bit_extract(value, 28U, 5U, &result);
```

is rejected.

### Full-width Extraction

The complete 32-bit value can be extracted:

```c
bit_extract(value, 0U, 32U, &result);
```

The result is equal to the original value.

## Testing

The unit tests are implemented in:

```text
bit_extract_test.c
```

The test suite contains 17 assertions.

### Normal Extraction Tests

The test suite verifies:

- Single-bit extraction.
- Extraction of bit 0.
- Extraction of bit 7.
- Multiple-bit extraction.
- Extraction from the middle of a value.
- Extraction from the upper byte.
- Full 32-bit extraction.

### Boundary Tests

The test suite verifies:

- Lower boundary of the input.
- Upper boundary of the input.
- Zero-value input.
- All-one input.

### Invalid Argument Tests

The following invalid conditions are tested:

- `NULL` result pointer.
- Zero extraction width.
- Invalid starting position.
- Extraction range exceeding 32 bits.

These tests verify both the returned status and the extracted value where applicable.

## Build

The module uses GCC and the provided Makefile.

Build the test executable:

```bash
make
```

The generated executable is:

```text
bit_extract_test
```

## Run Tests

Run the unit tests with:

```bash
make run
```

A successful test run should report:

```text
Tests: 17, Passed: 17, Failed: 0
```

The test program returns:

- `0` when all assertions pass.
- `1` when one or more assertions fail.

## Clean

Remove generated object files and the test executable:

```bash
make clean
```

## Complexity

The extraction operation uses a fixed number of arithmetic and bitwise operations.

- Time complexity: `O(1)`
- Space complexity: `O(1)`

The execution time does not depend on the position or width of the extracted field.

## Memory Management

The module does not perform dynamic memory allocation.

It does not use:

- `malloc()`
- `calloc()`
- `realloc()`
- `free()`

The caller provides the output storage through the `result` pointer.

## Embedded C Considerations

This module reinforces several low-level C concepts:

- Fixed-width integer types.
- Unsigned integer operations.
- Bitwise AND.
- Bit shifting.
- Bit masking.
- Integer promotions.
- Explicit type conversion.
- Boundary validation.
- Defensive programming.
- Deterministic execution.
- Avoidance of dynamic memory allocation.

Using `uint32_t` makes the intended input width explicit.

The `position` and `width` parameters use `uint8_t` because both represent values bounded by the 32-bit input width.

The implementation also handles the full-width case separately to avoid invalid shift operations.

## Typical Embedded Applications

Bit-field extraction is commonly used when processing structured binary data.

Typical applications include:

- Decoding communication protocol fields.
- Reading status and control registers.
- Extracting flags from packed data.
- Processing hardware register values.
- Parsing packed configuration data.
- Extracting fields from CAN or other automotive communication frames.
- Processing binary protocol headers.
- Implementing low-level serialization and deserialization logic.

This module itself is hardware-independent and does not directly access memory-mapped registers or communication peripherals.

## Limitations

The current implementation is intentionally limited to extracting fields from a 32-bit unsigned value.

It does not provide:

- Signed bit-field extraction.
- Sign extension.
- Extraction from multiple words.
- 64-bit input support.
- Hardware-specific register access.
- Compiler-specific intrinsics.

Signed interpretation of an extracted field is left to the caller.

## Files

```text
bit_extract/
├── README.md
├── Makefile
├── bit_extract.h
├── bit_extract.c
└── bit_extract_test.c
```

## Purpose

This module is part of an Embedded C practice repository focused on developing reliable low-level software through:

- Clear interfaces.
- Fixed-width integer types.
- Defensive programming.
- Explicit boundary handling.
- Bitwise operations.
- Unit testing.
- Reproducible builds.
- Hardware-independent implementations.