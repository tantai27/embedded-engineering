# Watchdog Simulator

A lightweight Embedded C watchdog simulator that models a basic software watchdog using a tick-based timeout mechanism.

The module simulates the core behavior of a hardware watchdog without requiring hardware or an RTOS.

## Overview

A watchdog is commonly used in embedded systems to detect software that stops responding or fails to service the system within an expected time interval.

This simulator models a watchdog using a software-controlled tick mechanism:

1. The watchdog is initialized with a timeout value.
2. The watchdog is started.
3. Each call to `watchdog_simulator_tick()` represents one elapsed tick.
4. The watchdog can be fed before the timeout is reached.
5. If the timeout is reached without being fed, the watchdog expires and stops running.
6. The watchdog can be started again to restart the timeout period.

The implementation is hardware-independent and does not require dynamic memory allocation.

## Project Structure

```text
watchdog_simulator/
├── watchdog_simulator.h
├── watchdog_simulator.c
├── watchdog_simulator_test.c
├── Makefile
└── README.md
```

## Files

| File | Description |
|---|---|
| `watchdog_simulator.h` | Public API, status codes, and watchdog control structure |
| `watchdog_simulator.c` | Watchdog state management and timeout logic |
| `watchdog_simulator_test.c` | Unit tests for the watchdog simulator |
| `Makefile` | Build, run, and clean automation |
| `README.md` | Module documentation |

## API

### `watchdog_simulator_init()`

Initializes the watchdog simulator.

```c
watchdog_simulator_status_t watchdog_simulator_init(
    watchdog_simulator_t * const watchdog,
    uint32_t timeout);
```

#### Parameters

| Parameter | Direction | Description |
|---|---|---|
| `watchdog` | `out` | Pointer to the watchdog control structure |
| `timeout` | `in` | Timeout duration in ticks |

The timeout must be greater than zero.

#### Behavior

On successful initialization:

- `timeout` is set to the configured timeout.
- `elapsed` is reset to `0U`.
- `running` is set to stopped.
- `expired` is set to active.

#### Return Status

- `WATCHDOG_SIMULATOR_STATUS_SUCCESS`
- `WATCHDOG_SIMULATOR_STATUS_INVALID_ARGUMENT`

---

### `watchdog_simulator_start()`

Starts or restarts the watchdog.

```c
watchdog_simulator_status_t watchdog_simulator_start(
    watchdog_simulator_t * const watchdog);
```

#### Behavior

Starting the watchdog:

- Resets `elapsed` to `0U`.
- Sets the watchdog to running.
- Clears the expired state.

Calling `start()` after the watchdog has expired starts a new timeout period.

#### Return Status

- `WATCHDOG_SIMULATOR_STATUS_SUCCESS`
- `WATCHDOG_SIMULATOR_STATUS_INVALID_ARGUMENT`

---

### `watchdog_simulator_feed()`

Feeds the watchdog and resets its elapsed time.

```c
watchdog_simulator_status_t watchdog_simulator_feed(
    watchdog_simulator_t * const watchdog);
```

#### Behavior

When the watchdog is running:

- `elapsed` is reset to `0U`.
- `expired` remains cleared.
- The watchdog continues running.

Feeding a stopped or expired watchdog does not restart it. `watchdog_simulator_start()` must be used to start a new watchdog cycle.

#### Return Status

- `WATCHDOG_SIMULATOR_STATUS_SUCCESS`
- `WATCHDOG_SIMULATOR_STATUS_INVALID_ARGUMENT`

---

### `watchdog_simulator_tick()`

Advances the watchdog by one tick.

```c
watchdog_simulator_status_t watchdog_simulator_tick(
    watchdog_simulator_t * const watchdog);
```

#### Behavior

If the watchdog is running:

- `elapsed` is incremented by one.
- Once `elapsed` reaches `timeout`, the watchdog expires.
- The watchdog is then stopped.

The elapsed counter is prevented from increasing beyond the configured timeout.

Example with a timeout of `3`:

```text
Start
  |
  v
elapsed = 0
  |
  | tick
  v
elapsed = 1
  |
  | tick
  v
elapsed = 2
  |
  | tick
  v
elapsed = 3
expired = 1
running = 0
```

#### Return Status

- `WATCHDOG_SIMULATOR_STATUS_SUCCESS`
- `WATCHDOG_SIMULATOR_STATUS_INVALID_ARGUMENT`

---

### `watchdog_simulator_is_expired()`

Returns the current expiration state.

```c
watchdog_simulator_status_t watchdog_simulator_is_expired(
    const watchdog_simulator_t * const watchdog,
    uint8_t * const expired);
```

#### Parameters

| Parameter | Direction | Description |
|---|---|---|
| `watchdog` | `in` | Pointer to the watchdog control structure |
| `expired` | `out` | Pointer receiving the expiration state |

The output value is:

```text
0U -> watchdog is active
1U -> watchdog has expired
```

#### Return Status

- `WATCHDOG_SIMULATOR_STATUS_SUCCESS`
- `WATCHDOG_SIMULATOR_STATUS_INVALID_ARGUMENT`

## Data Structure

The watchdog state is represented by:

```c
typedef struct
{
    uint32_t timeout;
    uint32_t elapsed;
    uint8_t running;
    uint8_t expired;
} watchdog_simulator_t;
```

### Fields

| Field | Description |
|---|---|
| `timeout` | Configured timeout in ticks |
| `elapsed` | Number of ticks elapsed since the last start/feed |
| `running` | Indicates whether the watchdog is currently running |
| `expired` | Indicates whether the watchdog has reached its timeout |

## State Model

The simulator uses explicit state information instead of relying on implicit behavior.

### Initial State

After initialization:

```text
running = 0
expired = 0
elapsed = 0
```

The watchdog is initialized but not running.

### Running State

After `watchdog_simulator_start()`:

```text
running = 1
expired = 0
elapsed = 0
```

Each tick increases `elapsed`.

### Fed State

When the watchdog is running, calling `watchdog_simulator_feed()` resets:

```text
elapsed = 0
expired = 0
```

The watchdog remains running.

### Expired State

When:

```text
elapsed >= timeout
```

the watchdog transitions to:

```text
running = 0
expired = 1
```

The elapsed value is retained at the configured timeout.

## Design Decisions

### No Dynamic Memory Allocation

The module does not use:

- `malloc()`
- `calloc()`
- `realloc()`
- `free()`

All watchdog state is stored in a caller-provided structure.

This makes the module suitable for embedded environments where dynamic allocation may be avoided.

### Tick-Based Timing

The module does not depend on a real-time clock, timer peripheral, operating system, or RTOS.

One call to:

```c
watchdog_simulator_tick()
```

represents one elapsed time unit.

The application determines the actual tick period.

For example, if one tick represents `10 ms` and the timeout is `100` ticks:

```text
timeout = 100 × 10 ms
       = 1000 ms
       = 1 second
```

### Explicit State Management

The watchdog keeps both:

- running state
- expiration state

This allows the module to distinguish between:

```text
Initialized but never started
Running
Stopped
Expired
```

### Defensive Argument Validation

Public APIs validate pointer arguments before dereferencing them.

Initialization also rejects a zero timeout because a zero-duration watchdog would not represent a meaningful timeout period.

### Saturating Elapsed Counter

The elapsed counter is incremented only while:

```text
elapsed < timeout
```

Once the timeout is reached, the counter does not continue increasing.

This avoids unnecessary counter growth and keeps the state deterministic.

### Restart Requires Explicit Start

Feeding an expired watchdog does not restart it.

Once expiration occurs:

```text
running = 0
expired = 1
```

A new watchdog cycle requires:

```c
watchdog_simulator_start(&watchdog);
```

This models a design where expiration represents a terminal event for the current watchdog cycle.

## Unit Tests

The test suite validates the main functional and boundary conditions of the module.

### Test Cases

| Test | Description |
|---|---|
| `test_init_success` | Verifies successful initialization and initial state |
| `test_init_invalid_arguments` | Verifies NULL pointer and zero-timeout validation |
| `test_start` | Verifies starting the watchdog |
| `test_tick_before_timeout` | Verifies elapsed time increases before expiration |
| `test_expiration_at_timeout` | Verifies expiration exactly at the configured timeout |
| `test_feed` | Verifies feeding resets elapsed time |
| `test_feed_prevents_expiration` | Verifies periodic feeding prevents expiration |
| `test_start_restarts_watchdog` | Verifies a new watchdog cycle can be started after expiration |
| `test_is_expired_invalid_arguments` | Verifies expiration-query argument validation |
| `test_null_arguments` | Verifies NULL handling for start, feed, and tick |

The test program returns:

```text
0
```

when all tests pass and:

```text
1
```

when one or more tests fail.

## Build Requirements

The project requires:

- GCC
- GNU Make
- C11-compatible compiler

The code is compiled with:

```text
-std=c11
-Wall
-Wextra
-Wpedantic
```

These compiler options help detect common C programming issues during development.

## Build

Run:

```bash
make
```

This builds:

```text
watchdog_simulator_test
```

## Run Tests

Run:

```bash
make run
```

or directly:

```bash
./watchdog_simulator_test
```

A successful run should produce output similar to:

```text
Tests: 33, Passed: 33, Failed: 0
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
| `run` | Builds and executes the unit tests |
| `clean` | Removes generated build artifacts |

## Complexity

Let `n` represent the number of ticks processed.

### Initialization

```text
Time:  O(1)
Space: O(1)
```

### Start

```text
Time:  O(1)
Space: O(1)
```

### Feed

```text
Time:  O(1)
Space: O(1)
```

### Tick

```text
Time:  O(1)
Space: O(1)
```

### Expiration Query

```text
Time:  O(1)
Space: O(1)
```

## Concepts Practiced

This module provides practice with several Embedded C concepts:

- Watchdog timer concepts
- Software timeout handling
- Tick-based timing
- Explicit state machines
- State transitions
- Defensive programming
- NULL pointer validation
- Fixed-width integer types
- `const` correctness
- Structure-based state management
- Boundary-condition handling
- Saturating counters
- Explicit status codes
- Hardware-independent embedded design
- Unit testing
- GCC warning levels
- Makefile-based builds

## Limitations

This module is a software simulation and does not interact with:

- Hardware watchdog peripherals
- MCU reset circuitry
- Interrupt handlers
- Hardware timers
- RTOS scheduler
- Real-time operating system services

Therefore, expiration only changes the simulator's internal state. It does not reset the processor or system.

## Example Usage

```c
#include "watchdog_simulator.h"

int main(void)
{
    watchdog_simulator_t watchdog;
    uint8_t expired = 0U;

    (void)watchdog_simulator_init(&watchdog, 5U);
    (void)watchdog_simulator_start(&watchdog);

    (void)watchdog_simulator_tick(&watchdog);
    (void)watchdog_simulator_tick(&watchdog);

    (void)watchdog_simulator_feed(&watchdog);

    (void)watchdog_simulator_tick(&watchdog);

    (void)watchdog_simulator_is_expired(&watchdog, &expired);

    return (expired == 0U) ? 0 : 1;
}
```

In this example, the watchdog is fed before the timeout is reached, so it remains active.