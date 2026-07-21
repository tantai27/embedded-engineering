# Set Bit

## Description

This module provides a simple API to set a specific bit in a 32-bit register.

The implementation follows common Embedded C practices:
- Defensive programming
- Input validation
- Clear API design
- Unit testing

---

## API

```c
status_t set_bit(volatile uint32_t * const reg, uint8_t pos);
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

- Use `volatile` to reflect register-like objects commonly found in embedded systems.
- Validate input arguments before performing any operation.
- Prevent undefined behavior by rejecting bit positions greater than or equal to the register width.
- Return status codes instead of terminating the program or using assertions.

---

## Test Cases

The following scenarios are verified:

- Set bit 0
- Set bit 31
- Set an already-set bit
- Set a bit in a non-zero register
- NULL pointer
- Invalid bit position

---

## Build

```bash
make
```

---

## Run

```bash
./set_bit_test
```

---

## Concepts Practiced

- Bitwise OR (`|`)
- Left shift (`<<`)
- Defensive programming
- Undefined behavior prevention
- Integer types (`uint32_t`, `uint8_t`)
- `volatile`
- Basic unit testing