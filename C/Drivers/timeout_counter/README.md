# Timeout Counter

## Overview

This module implements a simple software timeout counter for embedded
software.

The purpose of the exercise is to practice state management, counter-based
timing and boundary-condition handling in a small driver-style module.

The timeout is represented by a configurable number of software ticks.
Each call to `timeout_counter_tick()` advances the counter by one tick while
the timeout is running.

The implementation is expected to:

- Initialize a timeout counter with a configurable timeout value.
- Start and restart the timeout counter.
- Advance the counter one tick at a time.
- Detect when the configured timeout has been reached.
- Stop counting after the timeout expires.
- Keep elapsed time within the configured timeout value.
- Validate input arguments before accessing memory.
- Return explicit status codes.
- Avoid dynamic memory allocation.
- Use fixed-width integer types suitable for embedded systems.
- Follow defensive programming and clean Embedded C coding practices.

The module is intended to provide a small software abstraction that can be
used by embedded drivers or application logic that needs simple timeout
tracking without depending on hardware timers or an RTOS.

---

## Project Structure

```text
timeout_counter/
├── Makefile
├── README.md
├── timeout_counter.c
├── timeout_counter.h
└── timeout_counter_test.c
```

| File | Description |
|------|-------------|
| `timeout_counter.h` | Public API, status definitions and timeout control structure. |
| `timeout_counter.c` | Timeout initialization, start, tick and expiration implementation. |
| `timeout_counter_test.c` | Unit tests for initialization, ticking, expiration and restart behavior. |
| `Makefile` | Build, run and clean targets. |
| `README.md` | Module documentation and test information. |

---

## API

```c
timeout_counter_status_t timeout_counter_init(
    timeout_counter_t * const counter,
    uint32_t timeout);

timeout_counter_status_t timeout_counter_start(
    timeout_counter_t * const counter);

timeout_counter_status_t timeout_counter_tick(
    timeout_counter_t * const counter);

timeout_counter_status_t timeout_counter_is_expired(
    const timeout_counter_t * const counter,
    uint8_t * const expired);
```

### Parameters

| Parameter | Description |
|-----------|-------------|
| `counter` | Pointer to the timeout counter control structure. |
| `timeout` | Timeout duration expressed in software ticks. |
| `expired` | Pointer to store the timeout expiration state. |

---

## Timeout State

The control structure maintains:

| Field | Description |
|-------|-------------|
| `timeout` | Configured timeout duration in ticks. |
| `elapsed` | Number of ticks currently elapsed. |
| `running` | Indicates whether the counter is actively running. |

The timeout state can be represented as:

```text
Stopped
   |
   | start()
   v
Running
   |
   | tick() until elapsed == timeout
   v
Expired
```

After expiration, the counter stops automatically.

---

## Return Status

| Status | Description |
|--------|-------------|
| `TIMEOUT_COUNTER_STATUS_SUCCESS` | Operation completed successfully. |
| `TIMEOUT_COUNTER_STATUS_INVALID_ARGUMENT` | One or more input arguments are invalid. |

---

## Design Decisions

### Software tick model

The module does not directly access a hardware timer.

Instead, the caller provides the timing mechanism and calls:

```c
timeout_counter_tick(&counter);
```

once for every elapsed time unit.

For example, if one tick represents 1 ms:

```text
timeout = 100

tick() x 100 -> timeout expires after 100 ms
```

This keeps the module independent from a specific MCU, timer peripheral,
interrupt mechanism or RTOS.

### Start and restart behavior

Starting the timeout always resets the elapsed counter:

```text
elapsed = 0
running = true
```

Therefore, calling `timeout_counter_start()` on an already running counter
restarts the timeout from zero.

### Timeout boundary

The timeout expires when:

```text
elapsed >= timeout
```

The implementation increments `elapsed` only while it is below the configured
timeout.

This prevents the elapsed counter from growing beyond the configured timeout.

Conceptually:

```text
timeout = 3

elapsed:
0 -> 1 -> 2 -> 3
               ^
             expired
```

### Saturated counter

Once the timeout boundary is reached, `elapsed` remains equal to `timeout`.

Additional ticks do not increase the counter beyond the configured limit.

This avoids unnecessary counter growth and provides deterministic state.

### Defensive programming

The public APIs validate pointer arguments before accessing memory.

The initialization function also rejects:

```text
timeout == 0
```

because a zero-duration timeout would not provide a meaningful counting
interval for this module.

Invalid arguments return:

```text
TIMEOUT_COUNTER_STATUS_INVALID_ARGUMENT
```

### No dynamic memory allocation

The module does not use:

```text
malloc()
calloc()
realloc()
free()
```

The control structure is allocated by the caller, making memory usage
deterministic and suitable for embedded systems.

---

## Unit Tests

The unit tests verify:

- Timeout counter initialization.
- Initial elapsed value.
- Initial non-expired state.
- Starting the timeout.
- First tick processing.
- Elapsed counter update.
- Reaching the timeout boundary.
- Expiration detection.
- Restart behavior.
- Elapsed counter reset after restart.

### Test Cases

```text
[01/10] Timeout initialization
[02/10] Initial elapsed value
[03/10] Initial timeout state
[04/10] Start timeout
[05/10] First tick
[06/10] Elapsed after first tick
[07/10] Reach timeout boundary
[08/10] Timeout expired
[09/10] Restart timeout
[10/10] Elapsed reset after restart
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
make timeout_counter_test
```

The build produces:

```text
timeout_counter_test
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
Running timeout_counter unit tests
========================================
[01/10] Timeout initialization       [PASS]
[02/10] Initial elapsed value       [PASS]
[03/10] Initial timeout state       [PASS]
[04/10] Start timeout               [PASS]
[05/10] First tick                  [PASS]
[06/10] Elapsed after first tick    [PASS]
[07/10] Reach timeout boundary      [PASS]
[08/10] Timeout expired             [PASS]
[09/10] Restart timeout             [PASS]
[10/10] Elapsed reset after restart [PASS]
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
| `make timeout_counter_test` | Build the project explicitly. |
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
timeout_counter.o
timeout_counter_test.o
timeout_counter_test
```

---

## Concepts Practiced

- Software timeout
- Counter-based timing
- State management
- Start/restart behavior
- Timeout boundary handling
- Saturating counters
- Unsigned integer arithmetic
- Pointer validation
- Fixed-width integer types
- Defensive programming
- Explicit status reporting
- Deterministic memory usage
- Driver-style API design
- Unit testing
- Makefile
- Embedded C coding practices