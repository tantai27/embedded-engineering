# Bit Rotate

A lightweight Embedded C module for rotating the bits of an 8-bit unsigned value to the left or right.

Unlike a normal bit shift, bit rotation preserves all bits by moving the bits shifted out from one side back to the opposite side.

## Features

- Rotate an 8-bit value to the left.
- Rotate an 8-bit value to the right.
- Automatically normalize the rotation amount to the 8-bit width.
- Handle zero-bit and full-width rotations.
- Hardware-independent implementation.
- No dynamic memory allocation.
- Deterministic execution.
- Uses fixed-width integer types.

## API

### `bit_rotate_left()`

Rotates an 8-bit value to the left.

```c
uint8_t bit_rotate_left(
    uint8_t value,
    uint8_t shift);
```

Bits shifted out from the most significant side are inserted back into the least significant side.

Example:

```text
Input:  1010 0101
Shift:  1 bit left

Output: 0100 1011
```

Therefore:

```c
bit_rotate_left(0xA5U, 1U) == 0x4BU
```

### `bit_rotate_right()`

Rotates an 8-bit value to the right.

```c
uint8_t bit_rotate_right(
    uint8_t value,
    uint8_t shift);
```

Bits shifted out from the least significant side are inserted back into the most significant side.

Example:

```text
Input:  1010 0101
Shift:  1 bit right

Output: 1101 0010
```

Therefore:

```c
bit_rotate_right(0xA5U, 1U) == 0xD2U
```

## Bit Rotation

A bit rotation differs from a normal shift because no bit is discarded.

For example, a normal left shift:

```text
1010 0101 << 1
↓
0100 1010
```

The most significant bit is shifted out and lost.

A left rotation:

```text
1010 0101 rotate-left 1
↓
0100 1011
```

The bit shifted out from the most significant side is inserted at the least significant side.

Similarly, a right rotation moves bits from the least significant side back to the most significant side.

## Rotation Amount Normalization

The module operates on an 8-bit value, so the rotation amount is normalized to the 8-bit width.

Conceptually:

```text
effective_shift = shift % 8
```

This produces the expected behavior for rotation amounts greater than the value width.

For example:

```text
rotate_left(value, 8)  == value
rotate_left(value, 9)  == rotate_left(value, 1)
rotate_left(value, 16) == value
```

The same rule applies to right rotation.

## Implementation

For a non-zero left rotation, the implementation combines two shifted versions of the value:

```text
(value << shift) | (value >> (8 - shift))
```

For a non-zero right rotation:

```text
(value >> shift) | (value << (8 - shift))
```

The implementation explicitly handles a normalized shift of zero before performing the shift operations.

This prevents a shift operation from using the full width as the shift count.

## Boundary Conditions

The module handles the following conditions:

| Condition | Behavior |
|---|---|
| `shift == 0` | Original value is returned |
| `shift == 1` | One-bit rotation |
| `shift == 7` | Seven-bit rotation |
| `shift == 8` | Original value is returned |
| `shift > 8` | Rotation amount is normalized |
| `value == 0x00` | Result remains `0x00` |
| `value == 0xFF` | Result remains `0xFF` |

## Example

```c
#include <stdint.h>
#include <stdio.h>

#include "bit_rotate.h"

int main(void)
{
    uint8_t value = 0xA5U;
    uint8_t result = 0U;

    result = bit_rotate_left(value, 3U);

    printf("0x%02X\n", result);

    return 0;
}
```

The input value is:

```text
0xA5 = 1010 0101
```

Rotating left by three positions:

```text
1010 0101
↓
0010 1101
```

The result is:

```text
0x2D
```

## Testing

The unit tests are implemented in:

```text
bit_rotate_test.c
```

The test suite contains 15 assertions covering both left and right rotation.

### Left Rotation Tests

The following cases are tested:

- Zero-bit rotation.
- One-bit rotation.
- Multiple-bit rotation.
- Full-width rotation.
- Rotation amount normalization.
- All-zero input.
- All-one input.

### Right Rotation Tests

The following cases are tested:

- Zero-bit rotation.
- One-bit rotation.
- Multiple-bit rotation.
- Full-width rotation.
- Rotation amount normalization.
- All-zero input.
- All-one input.

### Inverse Rotation Test

The test suite also verifies that rotating a value in one direction and then rotating it back by the same amount restores the original value.

```c
rotated = bit_rotate_left(value, shift);
rotated = bit_rotate_right(rotated, shift);
```

The expected property is:

```text
rotate_right(rotate_left(value, shift), shift) == value
```

## Build

The module uses GCC and a simple Makefile.

Build the test executable:

```bash
make
```

This produces:

```text
bit_rotate_test
```

## Run Tests

Run the unit tests with:

```bash
make run
```

A successful test run reports:

```text
Tests: 15, Passed: 15, Failed: 0
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

Both rotation functions have constant complexity:

- Time complexity: `O(1)`
- Space complexity: `O(1)`

The number of operations does not depend on the rotation amount.

## Memory Management

This module does not perform dynamic memory allocation.

It does not use:

- `malloc()`
- `calloc()`
- `realloc()`
- `free()`

All operations work directly with values supplied by the caller.

## Embedded C Considerations

This module reinforces several low-level C concepts:

- Bitwise operators.
- Fixed-width integer types.
- Unsigned integer handling.
- Integer promotions.
- Shift operations.
- Shift boundary conditions.
- Explicit type conversion.
- Deterministic execution.
- Avoidance of dynamic memory allocation.

The use of `uint8_t` makes the intended data width explicit.

The shift amount is normalized before rotation, and the zero-shift case is handled separately to avoid invalid shift operations.

## Typical Embedded Applications

Bit rotation can be useful in low-level software and algorithms involving bit-level transformations, including:

- Checksum and CRC-related processing.
- Hashing algorithms.
- Bit-field transformations.
- Lightweight encoding and decoding.
- Cryptographic primitives.
- Register and protocol data manipulation.

This module itself is hardware-independent and does not access memory-mapped registers or peripherals.

## Limitations

The current implementation intentionally supports only 8-bit values.

It does not provide:

- 16-bit rotation.
- 32-bit rotation.
- 64-bit rotation.
- Architecture-specific rotate instructions.
- Compiler-specific rotate intrinsics.

These variants can be implemented separately when required by a target platform.

## Files

```text
bit_rotate/
├── README.md
├── Makefile
├── bit_rotate.h
├── bit_rotate.c
└── bit_rotate_test.c
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