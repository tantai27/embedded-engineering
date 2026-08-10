# Ring Buffer

## Overview

This module implements a fixed-size byte ring buffer for embedded software.

The purpose of the exercise is to practice a common circular-buffer pattern used
in embedded systems for data streams such as UART, communication interfaces,
drivers, and producer-consumer data paths.

The implementation is expected to:

* Initialize a fixed-size ring buffer with externally provided storage.
* Add (`push`) one byte to the buffer.
* Remove (`pop`) one byte from the buffer.
* Automatically wrap read and write indices when reaching the buffer boundary.
* Detect full and empty buffer conditions.
* Validate all input arguments before accessing memory.
* Maintain buffer state explicitly through read index, write index, and element count.
* Avoid dynamic memory allocation.
* Provide explicit status reporting for each operation.
* Follow defensive programming and clean Embedded C coding practices.

The implementation should keep the buffer storage separate from its control
structure so that the same API can operate on statically allocated memory
suitable for embedded systems.

## Project Structure

```text
ring_buffer/
├── Makefile
├── README.md
├── ring_buffer.c
├── ring_buffer.h
└── ring_buffer_test.c
```

| File                 | Description                                                                 |
| -------------------- | --------------------------------------------------------------------------- |
| `ring_buffer.h`      | Public API, status definitions and ring buffer control structure.           |
| `ring_buffer.c`      | Ring buffer initialization, push and pop implementation.                    |
| `ring_buffer_test.c` | Unit tests for normal operation, boundary conditions and invalid arguments. |
| `Makefile`           | Build, run and clean targets.                                               |

---

## API

```c
ring_buffer_status_t ring_buffer_init(ring_buffer_t * const rb,
                                      uint8_t * const buffer,
                                      uint32_t capacity);

ring_buffer_status_t ring_buffer_push(ring_buffer_t * const rb,
                                      uint8_t data);

ring_buffer_status_t ring_buffer_pop(ring_buffer_t * const rb,
                                     uint8_t * const data);
```

### Ring Buffer State

The control structure maintains:

| Field         | Description                                     |
| ------------- | ----------------------------------------------- |
| `buffer`      | Pointer to externally allocated storage.        |
| `capacity`    | Maximum number of bytes the buffer can contain. |
| `read_index`  | Index of the next byte to be removed.           |
| `write_index` | Index where the next byte will be stored.       |
| `count`       | Number of bytes currently stored.               |

### Return Status

| Status                                | Description                                               |
| ------------------------------------- | --------------------------------------------------------- |
| `RING_BUFFER_STATUS_SUCCESS`          | Operation completed successfully.                         |
| `RING_BUFFER_STATUS_FULL`             | Push operation cannot proceed because the buffer is full. |
| `RING_BUFFER_STATUS_EMPTY`            | Pop operation cannot proceed because the buffer is empty. |
| `RING_BUFFER_STATUS_INVALID_ARGUMENT` | One or more input arguments are invalid.                  |

---

## Design Decisions

### Fixed-size storage

The ring buffer does not allocate memory dynamically.

Storage is provided by the caller:

```c
uint8_t buffer[8U];
ring_buffer_t rb;
```

This makes the implementation suitable for embedded environments where
deterministic memory usage is preferred and dynamic allocation may be avoided.

### Explicit buffer state

The implementation tracks three pieces of state:

```text
read_index
write_index
count
```

`count` is used to distinguish the full and empty states without requiring a
reserved slot.

The valid states are therefore:

```text
count == 0          -> empty
count < capacity    -> partially filled
count == capacity   -> full
```

### Index wraparound

When an index reaches the buffer capacity, it returns to zero.

Conceptually:

```text
0 -> 1 -> 2 -> ... -> capacity - 1 -> 0 -> ...
```

This allows the same storage area to be reused continuously.

### FIFO behavior

Data is removed in the same order in which it was inserted.

For example:

```text
push: A -> B -> C

pop:  A -> B -> C
```

This makes the ring buffer suitable for sequential byte streams such as UART
receive/transmit paths.

### Defensive programming

All public APIs validate pointer arguments before accessing memory.

The implementation also checks:

* Zero buffer capacity during initialization.
* Full buffer before `push`.
* Empty buffer before `pop`.

Invalid operations return an explicit status instead of accessing invalid memory
or silently corrupting buffer state.

---

## Unit Tests

The unit tests verify the following scenarios:

* Ring buffer initialization.
* Invalid initialization arguments.
* Basic push and pop operation.
* FIFO ordering.
* Full buffer detection.
* Empty buffer detection.
* Read/write index wraparound.
* Invalid push argument.
* Invalid pop arguments.

The wraparound test is particularly important because circular indexing is the
core behavior that distinguishes a ring buffer from a normal linear buffer.

---

## Requirements

* GCC (C11 or later)
* GNU Make

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

or:

```bash
make ring_buffer
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
Running ring_buffer unit tests
========================================
[01/09] Initialize ring buffer        [PASS]
[02/09] Invalid initialization        [PASS]
[03/09] Push and pop                  [PASS]
[04/09] FIFO order                    [PASS]
[05/09] Full buffer                   [PASS]
[06/09] Empty buffer                  [PASS]
[07/09] Index wraparound              [PASS]
[08/09] Invalid push argument         [PASS]
[09/09] Invalid pop argument          [PASS]
----------------------------------------
Summary
----------------------------------------
Executed : 9/9
Passed   : 9/9 (100%)
Failed   : 0/9 (0%)
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

* Circular buffer
* FIFO data flow
* Read/write index management
* Index wraparound
* Buffer full and empty states
* Structure-based state management
* Pointer validation
* Defensive programming
* Static memory allocation
* `uint8_t`
* `uint32_t`
* Embedded data buffering
* Unit testing
* Makefile
