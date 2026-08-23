# Queue

## Overview

This module implements a fixed-size FIFO queue for Embedded C.

The purpose of the exercise is to practice queue data structures, FIFO data
flow, index management and explicit state handling in a resource-constrained
embedded environment.

The implementation uses externally provided static storage and does not
perform dynamic memory allocation.

The implementation is expected to:

- Initialize a fixed-size queue with externally provided storage.
- Add (`push`) elements to the queue.
- Remove (`pop`) elements in FIFO order.
- Detect full and empty queue conditions.
- Automatically wrap head and tail indices.
- Maintain queue state explicitly.
- Validate input arguments before accessing memory.
- Return explicit status codes for each operation.
- Avoid dynamic memory allocation.
- Use fixed-width integer types suitable for embedded systems.
- Follow defensive programming and clean Embedded C coding practices.

The queue should provide a small and reusable API suitable for buffering
commands, messages, events or other sequential data in embedded software.

---

## Project Structure

```text
queue/
├── Makefile
├── README.md
├── queue.c
├── queue.h
└── queue_test.c
```

| File | Description |
|------|-------------|
| `queue.h` | Public API, status definitions and queue control structure. |
| `queue.c` | Queue initialization, push and pop implementation. |
| `queue_test.c` | Unit tests for initialization, FIFO behavior, boundaries and invalid arguments. |
| `Makefile` | Build, run and clean targets. |
| `README.md` | Module documentation and test information. |

---

## API

```c
queue_status_t queue_init(queue_t * const queue,
                           uint32_t * const buffer,
                           uint32_t capacity);

queue_status_t queue_push(queue_t * const queue,
                           uint32_t data);

queue_status_t queue_pop(queue_t * const queue,
                          uint32_t * const data);
```

### Queue State

The control structure maintains:

| Field | Description |
|-------|-------------|
| `buffer` | Pointer to externally allocated queue storage. |
| `capacity` | Maximum number of elements the queue can contain. |
| `head` | Index of the next element to be removed. |
| `tail` | Index where the next element will be inserted. |
| `count` | Number of elements currently stored. |

---

## Return Status

| Status | Description |
|--------|-------------|
| `QUEUE_STATUS_SUCCESS` | Operation completed successfully. |
| `QUEUE_STATUS_FULL` | Queue cannot accept another element. |
| `QUEUE_STATUS_EMPTY` | Queue contains no elements to remove. |
| `QUEUE_STATUS_INVALID_ARGUMENT` | One or more input arguments are invalid. |

---

## Design Decisions

### Fixed-size storage

The queue does not allocate memory dynamically.

Storage is provided by the caller:

```c
uint32_t buffer[3U];
queue_t queue;
```

This makes memory usage deterministic and suitable for embedded systems.

### FIFO behavior

The queue follows First-In, First-Out ordering.

For example:

```text
push: 10 -> 20 -> 30

pop:  10 -> 20 -> 30
```

The first element inserted is always the first element removed.

### Explicit queue state

The implementation tracks:

```text
head
tail
count
```

The `count` field is used to distinguish empty and full states.

The valid states are:

```text
count == 0          -> empty
count < capacity    -> partially filled
count == capacity   -> full
```

### Index wraparound

Both `head` and `tail` wrap back to zero when reaching the queue capacity.

Conceptually:

```text
0 -> 1 -> 2 -> ... -> capacity - 1 -> 0 -> ...
```

This allows the queue to continuously reuse the same storage.

### Defensive programming

The public APIs validate pointer arguments before accessing memory.

The implementation also checks:

- Zero capacity during initialization.
- Full queue before `push`.
- Empty queue before `pop`.
- `NULL` output pointer during `pop`.

Invalid operations return an explicit status instead of accessing invalid memory
or corrupting queue state.

### No dynamic memory allocation

The implementation does not use:

```text
malloc()
calloc()
realloc()
free()
```

All storage is supplied by the caller.

---

## Unit Tests

The unit tests verify:

- Queue initialization.
- `NULL` queue initialization.
- `NULL` buffer initialization.
- Zero-capacity initialization.
- Push operation.
- Multiple push operations.
- Full queue detection.
- FIFO ordering of the first element.
- FIFO ordering of the second element.

### Test Cases

```text
[01/10] Queue initialization
[02/10] Null queue initialization
[03/10] Null buffer initialization
[04/10] Zero capacity initialization
[05/10] Push first element
[06/10] Push second element
[07/10] Push third element
[08/10] Full queue detection
[09/10] FIFO first element
[10/10] FIFO second element
```

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

Build the unit test executable:

```bash
make
```

or:

```bash
make queue_test
```

The build produces:

```text
queue_test
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
Running queue unit tests
========================================
[01/10] Queue initialization          [PASS]
[02/10] Null queue initialization    [PASS]
[03/10] Null buffer initialization  [PASS]
[04/10] Zero capacity initialization [PASS]
[05/10] Push first element           [PASS]
[06/10] Push second element          [PASS]
[07/10] Push third element           [PASS]
[08/10] Full queue detection         [PASS]
[09/10] FIFO first element           [PASS]
[10/10] FIFO second element          [PASS]
----------------------------------------
Summary
----------------------------------------
Executed : 10/10
Passed   : 10/10 (100%)
Failed   : 0/10 (0%)
========================================
```

A successful test run returns `EXIT_SUCCESS`.

If one or more tests fail, the test executable returns `EXIT_FAILURE`.

---

## Makefile Targets

| Target | Description |
|--------|-------------|
| `make` | Build the unit test executable. |
| `make queue_test` | Build the project explicitly. |
| `make run` | Build and execute all unit tests. |
| `make clean` | Remove generated build artifacts. |

---

## Clean

Remove generated build artifacts:

```bash
make clean
```

This removes:

```text
queue.o
queue_test.o
queue_test
```

---

## Concepts Practiced

- FIFO queue
- Queue state management
- Head and tail indices
- Index wraparound
- Full and empty conditions
- Static memory allocation
- External buffer management
- Pointer validation
- Fixed-width integer types
- Defensive programming
- Explicit status reporting
- Unit testing
- Makefile
- Embedded C coding practices