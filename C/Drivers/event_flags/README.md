# Event Flags

A lightweight Embedded C event flags module that provides a software mechanism for storing and checking multiple event states using a 32-bit bitmask.

The module models a common embedded and RTOS concept where individual bits represent independent events or conditions.

The implementation is hardware-independent, does not require an RTOS, and does not use dynamic memory allocation.

## Overview

Event flags provide a compact way to represent multiple independent events in a single integer.

Each bit of the 32-bit event flag field can represent one event:

```text
Bit 31                       Bit 0
  |                            |
  v                            v
+--+--+--+--+--+--+--+--+-----+
|  |  |  |  |  |  |  |  | ... |
+--+--+--+--+--+--+--+--+-----+
```

For example:

```text
0x00000001 -> Event 0
0x00000002 -> Event 1
0x00000004 -> Event 2
0x00000008 -> Event 3
```

Multiple events can be represented simultaneously:

```text
0x00000005
```

which means:

```text
Event 0 = set
Event 1 = clear
Event 2 = set
```

The module provides operations to:

- Initialize event flags.
- Set one or more flags.
- Clear one or more flags.
- Read the current flag state.
- Check whether all requested flags are set.

## Project Structure

```text
event_flags/
├── event_flags.h
├── event_flags.c
├── event_flags_test.c
├── Makefile
└── README.md
```

## Files

| File | Description |
|---|---|
| `event_flags.h` | Public API, status codes, and event flags structure |
| `event_flags.c` | Event flag operations |
| `event_flags_test.c` | Unit tests |
| `Makefile` | Build, test, and clean automation |
| `README.md` | Module documentation |

## API

### `event_flags_init()`

Initializes the event flags object.

```c
event_flags_status_t event_flags_init(
    event_flags_t * const event_flags);
```

#### Parameters

| Parameter | Direction | Description |
|---|---|---|
| `event_flags` | `out` | Pointer to the event flags control structure |

#### Behavior

All event flags are cleared during initialization:

```text
flags = 0x00000000
```

#### Return Status

- `EVENT_FLAGS_STATUS_SUCCESS`
- `EVENT_FLAGS_STATUS_INVALID_ARGUMENT`

---

### `event_flags_set()`

Sets one or more event flags.

```c
event_flags_status_t event_flags_set(
    event_flags_t * const event_flags,
    uint32_t mask);
```

#### Parameters

| Parameter | Direction | Description |
|---|---|---|
| `event_flags` | `in,out` | Pointer to the event flags control structure |
| `mask` | `in` | Bit mask specifying the flags to set |

The operation is equivalent to:

```c
event_flags->flags |= mask;
```

#### Example

Initial state:

```text
flags = 0x00000003
```

Set:

```text
mask = 0x00000004
```

Result:

```text
flags = 0x00000007
```

#### Return Status

- `EVENT_FLAGS_STATUS_SUCCESS`
- `EVENT_FLAGS_STATUS_INVALID_ARGUMENT`

---

### `event_flags_clear()`

Clears one or more event flags.

```c
event_flags_status_t event_flags_clear(
    event_flags_t * const event_flags,
    uint32_t mask);
```

#### Parameters

| Parameter | Direction | Description |
|---|---|---|
| `event_flags` | `in,out` | Pointer to the event flags control structure |
| `mask` | `in` | Bit mask specifying the flags to clear |

The operation is equivalent to:

```c
event_flags->flags &= ~mask;
```

#### Example

Initial state:

```text
flags = 0x0000000F
```

Clear:

```text
mask = 0x00000005
```

Result:

```text
flags = 0x0000000A
```

#### Return Status

- `EVENT_FLAGS_STATUS_SUCCESS`
- `EVENT_FLAGS_STATUS_INVALID_ARGUMENT`

---

### `event_flags_get()`

Returns the current event flags.

```c
event_flags_status_t event_flags_get(
    const event_flags_t * const event_flags,
    uint32_t * const flags);
```

#### Parameters

| Parameter | Direction | Description |
|---|---|---|
| `event_flags` | `in` | Pointer to the event flags control structure |
| `flags` | `out` | Pointer receiving the current flag state |

#### Example

```c
uint32_t flags = 0U;

(void)event_flags_get(&event_flags, &flags);
```

After a successful call, `flags` contains the current event flag state.

#### Return Status

- `EVENT_FLAGS_STATUS_SUCCESS`
- `EVENT_FLAGS_STATUS_INVALID_ARGUMENT`

---

### `event_flags_are_set()`

Checks whether all flags specified by a mask are currently set.

```c
event_flags_status_t event_flags_are_set(
    const event_flags_t * const event_flags,
    uint32_t mask,
    uint8_t * const set);
```

#### Parameters

| Parameter | Direction | Description |
|---|---|---|
| `event_flags` | `in` | Pointer to the event flags control structure |
| `mask` | `in` | Required event flags |
| `set` | `out` | Pointer receiving the result |

The operation checks:

```c
(event_flags->flags & mask) == mask
```

If all requested bits are set:

```text
set = 1U
```

Otherwise:

```text
set = 0U
```

#### Example

Current state:

```text
flags = 0x0000000F
```

Check:

```text
mask = 0x00000005
```

Both bit 0 and bit 2 are set, therefore:

```text
set = 1U
```

If the current state is:

```text
flags = 0x00000005
```

and the requested mask is:

```text
mask = 0x00000003
```

bit 1 is missing, therefore:

```text
set = 0U
```

#### Zero Mask

A zero mask is considered satisfied because there are no required bits:

```text
(flags & 0U) == 0U
```

Therefore:

```text
event_flags_are_set(..., 0U, &set)
```

returns:

```text
set = 1U
```

## Data Structure

The module stores the event state in a single 32-bit value:

```c
typedef struct
{
    uint32_t flags;
} event_flags_t;
```

### Event Representation

Each bit can represent an independent event.

For example:

```text
Bit 0 -> EVENT_DATA_READY
Bit 1 -> EVENT_TIMEOUT
Bit 2 -> EVENT_ERROR
Bit 3 -> EVENT_TRANSMISSION_COMPLETE
```

A possible mask definition in an application could be:

```c
#define EVENT_DATA_READY             (1UL << 0U)
#define EVENT_TIMEOUT                (1UL << 1U)
#define EVENT_ERROR                  (1UL << 2U)
#define EVENT_TRANSMISSION_COMPLETE (1UL << 3U)
```

Multiple events can then be combined:

```c
uint32_t mask = EVENT_DATA_READY | EVENT_ERROR;
```

## Bitmask Operations

The implementation uses standard bitwise operations.

### Set Bits

```c
flags |= mask;
```

Any bit set in `mask` becomes set in `flags`.

```text
flags:  1010
mask:   0101
        ----
result: 1111
```

### Clear Bits

```c
flags &= ~mask;
```

Any bit set in `mask` becomes cleared in `flags`.

```text
flags:  1111
mask:   0101
~mask:  1010
        ----
result: 1010
```

### Check Bits

```c
(flags & mask) == mask
```

This verifies that every requested bit is set.

```text
flags:  1101
mask:   0101
        ----
AND:    0101
```

Since the result equals the requested mask, all requested events are set.

## Design Decisions

### 32-Bit Event Storage

The module uses `uint32_t` to provide up to 32 independent event flags.

This provides a compact representation while using a fixed-width integer type suitable for embedded systems.

### No Dynamic Memory Allocation

The module does not use:

- `malloc()`
- `calloc()`
- `realloc()`
- `free()`

The event flag state is stored directly inside a caller-provided structure.

### Hardware Independent

The module does not depend on:

- MCU peripherals
- interrupts
- hardware registers
- RTOS APIs
- operating-system primitives

This makes it possible to unit-test the logic on a host machine.

### Explicit Status Codes

Each public API returns an explicit status:

```c
typedef enum
{
    EVENT_FLAGS_STATUS_SUCCESS = 0U,
    EVENT_FLAGS_STATUS_INVALID_ARGUMENT
} event_flags_status_t;
```

This avoids relying on implicit error handling.

### Defensive Programming

All public functions validate pointer arguments before dereferencing them.

For example:

```c
if (NULL == event_flags)
{
    return EVENT_FLAGS_STATUS_INVALID_ARGUMENT;
}
```

Output pointers are also validated before writing results.

### Const Correctness

Read-only APIs use `const` pointers:

```c
const event_flags_t * const event_flags
```

This makes the intended access mode explicit and prevents accidental modification of the event flag object through the API.

## Unit Tests

The test suite covers the main operations and boundary conditions of the module.

### Initialization Tests

- Successful initialization.
- NULL pointer validation.
- Verification that initialization clears all flags.

### Set Tests

- Set a single flag.
- Set multiple flags.
- Set an already-set flag.
- Set all 32 flags.

### Clear Tests

- Clear a single flag.
- Clear multiple flags.
- Clear an already-cleared flag.
- Clear all 32 flags.

### Get Tests

- Read the current flag state.
- NULL event flag pointer.
- NULL output pointer.

### Flag Check Tests

- Verify all requested flags are set.
- Verify partial flags are not considered set.
- Verify zero mask behavior.
- Verify all 32 flags.
- Validate NULL arguments.

### Boundary Test

Bit 31 is explicitly tested:

```text
0x80000000
```

This verifies that the highest bit of the 32-bit event flag field can be correctly set, checked, and cleared.

## Test Summary

The test suite contains **33 assertions** covering:

```text
Initialization
Set operations
Clear operations
Get operation
Flag checking
NULL argument handling
Boundary bit 31
```

A successful test run reports:

```text
Tests: 33, Passed: 33, Failed: 0
```

## Build Requirements

The project requires:

- GCC
- GNU Make
- C11-compatible compiler

The project is compiled with:

```text
-std=c11
-Wall
-Wextra
-Wpedantic
```

These warning options help identify common C programming issues during development.

## Build

Run:

```bash
make
```

This produces:

```text
event_flags_test
```

## Run Tests

Run:

```bash
make run
```

or directly:

```bash
./event_flags_test
```

Expected output:

```text
Tests: 33, Passed: 33, Failed: 0
```

A successful test run returns exit code:

```text
0
```

If any assertion fails, the test executable returns:

```text
1
```

## Clean

Remove generated object files and the test executable:

```bash
make clean
```

## Makefile Targets

| Target | Description |
|---|---|
| `all` | Builds the test executable |
| `run` | Builds and runs the unit tests |
| `clean` | Removes generated build artifacts |

## Complexity

All public operations perform a constant number of operations.

| Function | Time | Space |
|---|---:|---:|
| `event_flags_init()` | O(1) | O(1) |
| `event_flags_set()` | O(1) | O(1) |
| `event_flags_clear()` | O(1) | O(1) |
| `event_flags_get()` | O(1) | O(1) |
| `event_flags_are_set()` | O(1) | O(1) |

The module requires only the caller-provided `event_flags_t` object and does not allocate additional memory.

## Concepts Practiced

This module provides practice with:

- Bitwise OR
- Bitwise AND
- Bitwise NOT
- Bitmask operations
- Event flag representation
- Multi-event state management
- Fixed-width integer types
- `const` correctness
- Defensive programming
- NULL pointer validation
- Explicit status codes
- Boundary conditions
- Hardware-independent Embedded C design
- Unit testing
- GCC warning levels
- Makefile-based builds

## Limitations

This module provides only the basic event flag storage and checking mechanism.

It does not implement:

- Blocking waits
- Timeouts
- Interrupt synchronization
- Thread synchronization
- RTOS scheduling
- Atomic operations
- Mutexes
- Semaphores
- Hardware event sources

Therefore, the module is a software representation of event flags rather than a complete RTOS synchronization primitive.

If the module is accessed concurrently by multiple execution contexts, additional synchronization or atomic access mechanisms may be required.

## Example Usage

```c
#include "event_flags.h"

#define EVENT_DATA_READY    (1UL << 0U)
#define EVENT_ERROR         (1UL << 1U)
#define EVENT_TX_COMPLETE   (1UL << 2U)

int main(void)
{
    event_flags_t event_flags;
    uint8_t set = 0U;

    (void)event_flags_init(&event_flags);

    (void)event_flags_set(
        &event_flags,
        EVENT_DATA_READY | EVENT_TX_COMPLETE);

    (void)event_flags_are_set(
        &event_flags,
        EVENT_DATA_READY | EVENT_TX_COMPLETE,
        &set);

    return (set == 1U) ? 0 : 1;
}
```

In this example, `EVENT_DATA_READY` and `EVENT_TX_COMPLETE` are both set, so the requested event mask is satisfied.