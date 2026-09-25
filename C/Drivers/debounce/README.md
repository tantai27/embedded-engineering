# Debounce

## Overview

`debounce` is a small Embedded C module for filtering unstable digital input signals such as mechanical buttons and switches.

Mechanical contacts can rapidly alternate between logical states when pressed or released. This behavior, commonly called **switch bounce**, can cause a single physical action to be interpreted as multiple input transitions.

The module uses a consecutive-sample debounce algorithm. A new input state is accepted only after it remains unchanged for a configured number of consecutive samples.

---

## Features

- Debounce binary digital input signals.
- Configurable stability threshold.
- Explicit initialization.
- Explicit status codes.
- Defensive argument validation.
- No dynamic memory allocation.
- Deterministic execution.
- Hardware-independent implementation.
- Suitable for GPIO and button driver integration.

---

## Design

The module maintains two logical states:

- **Stable state** — the currently accepted input state.
- **Candidate state** — the new input state currently being evaluated.

When the raw input changes, it becomes the candidate state and the consecutive-sample counter starts from one.

If subsequent samples remain equal to the candidate state, the counter increases.

Once the counter reaches `stable_ticks`, the candidate state becomes the new stable state.

```text
Raw input
   │
   ▼
┌──────────────────────────┐
│        Debounce          │
│                          │
│  Candidate state         │
│  Consecutive tick count  │
│  Stable state            │
└────────────┬─────────────┘
             │
             ▼
       Stable output
```

---

## Example

Assume:

```text
stable_ticks = 3
```

and the raw input contains switch bouncing:

```text
Raw:
0 0 1 0 1 1 1 1 1
```

The debounced output remains unchanged until three consecutive `1` samples have been received:

```text
Stable:
0 0 0 0 0 0 1 1 1
```

The short transitions are therefore ignored.

---

## API

### `debounce_init()`

```c
debounce_status_t debounce_init(
    debounce_t * const debounce,
    uint8_t initial_state,
    uint32_t stable_ticks);
```

Initializes a debounce instance.

#### Parameters

| Parameter | Type | Description |
|---|---|---|
| `debounce` | `debounce_t *` | Pointer to the debounce instance |
| `initial_state` | `uint8_t` | Initial stable state (`0U` or `1U`) |
| `stable_ticks` | `uint32_t` | Number of consecutive samples required to accept a new state |

`stable_ticks` must be greater than zero.

#### Return values

| Status | Meaning |
|---|---|
| `DEBOUNCE_STATUS_SUCCESS` | Initialization completed successfully |
| `DEBOUNCE_STATUS_INVALID_ARGUMENT` | Invalid pointer, state, or tick configuration |

---

### `debounce_update()`

```c
debounce_status_t debounce_update(
    debounce_t * const debounce,
    uint8_t raw_state,
    uint8_t * const stable_state);
```

Processes one raw input sample and returns the current debounced state.

The stable state changes only after the candidate state has remained unchanged for the configured number of consecutive updates.

#### Parameters

| Parameter | Type | Description |
|---|---|---|
| `debounce` | `debounce_t *` | Pointer to the debounce instance |
| `raw_state` | `uint8_t` | Current raw input state (`0U` or `1U`) |
| `stable_state` | `uint8_t *` | Pointer to store the current stable state |

#### Return values

| Status | Meaning |
|---|---|
| `DEBOUNCE_STATUS_SUCCESS` | Input sample processed successfully |
| `DEBOUNCE_STATUS_INVALID_ARGUMENT` | Invalid pointer or raw input state |

---

## Data Structure

The debounce state is represented by:

```c
typedef struct
{
    uint32_t stable_ticks;
    uint32_t consecutive_ticks;
    uint8_t stable_state;
    uint8_t candidate_state;
} debounce_t;
```

### `stable_ticks`

Number of consecutive samples required before accepting a new state.

### `consecutive_ticks`

Number of consecutive samples currently matching the candidate state.

The counter saturates at `stable_ticks` and does not continue increasing after the candidate state has already become stable.

### `stable_state`

The currently accepted and debounced input state.

### `candidate_state`

The raw input state currently being evaluated.

---

## State Transition

With `stable_ticks = 3`:

```text
Initial stable state = 0

Raw input:          1
Candidate state:    1
Consecutive ticks:  1
Stable state:       0

Raw input:          1
Candidate state:    1
Consecutive ticks:  2
Stable state:       0

Raw input:          1
Candidate state:    1
Consecutive ticks:  3
Stable state:       1
```

If the raw input changes before the threshold is reached:

```text
Raw:                 1 → 1 → 0

Candidate:           1 → 1 → 0
Consecutive ticks:   1 → 2 → 1
```

The previous candidate is discarded and the new state starts a new debounce sequence.

---

## Sampling Model

The module does not provide its own timer.

The caller is responsible for invoking `debounce_update()` periodically.

For example:

```text
Hardware timer
      │
      ▼
Periodic task
      │
      ▼
Read GPIO
      │
      ▼
debounce_update()
      │
      ▼
Stable button state
```

If `debounce_update()` is called every 1 ms and:

```text
stable_ticks = 10
```

then a new state must remain stable for approximately 10 ms before being accepted.

The actual timing depends on the caller's sampling period and scheduling accuracy.

---

## Embedded C Considerations

The implementation is designed with common embedded software practices:

- Fixed-width integer types.
- No dynamic memory allocation.
- Explicit initialization.
- Explicit status handling.
- Defensive pointer validation.
- No global mutable state.
- Deterministic execution.
- Saturating counter behavior.
- Hardware-independent core logic.

The module can therefore be integrated into bare-metal firmware, RTOS-based applications, or higher-level GPIO drivers.

---

## Applications

Typical applications include:

- Mechanical push buttons.
- Toggle switches.
- GPIO input filtering.
- Embedded user interfaces.
- Control panels.
- Digital control inputs.
- Button driver components.

---

## Unit Tests

The test suite contains 10 test cases covering both normal operation and invalid input handling.

| # | Test | Purpose |
|---|---|---|
| 1 | Initialization success | Verify normal initialization |
| 2 | Initialization NULL pointer | Validate NULL debounce pointer handling |
| 3 | Initialization zero ticks | Reject zero stability threshold |
| 4 | Initialization invalid state | Reject states other than `0U` and `1U` |
| 5 | Stable input unchanged | Verify an already stable input remains unchanged |
| 6 | Transition after required ticks | Verify a new state is accepted after the configured threshold |
| 7 | Bouncing input filtered | Verify unstable transitions do not change the stable state |
| 8 | Candidate counter reset | Verify a changed candidate restarts the consecutive counter |
| 9 | State transition back | Verify the stable state can transition in the opposite direction |
| 10 | Invalid update arguments | Validate NULL pointers and invalid raw input |

The tests also verify internal state behavior such as candidate tracking and consecutive-sample counting.

---

## Build

The project uses GCC and a Makefile.

### Build

```bash
make
```

Expected output:

```text
[debounce] $ make
CC      debounce.c
CC      debounce_test.c
LINK    debounce_test
```

### Run tests

```bash
make run
```

Expected result:

```text
========================================
Running debounce unit tests
========================================
[01/10] Initialization success         [PASS]
[02/10] Initialization NULL pointer    [PASS]
[03/10] Initialization zero ticks      [PASS]
[04/10] Initialization invalid state  [PASS]
[05/10] Stable input unchanged         [PASS]
[06/10] Transition after required ticks [PASS]
[07/10] Bouncing input filtered        [PASS]
[08/10] Candidate counter reset        [PASS]
[09/10] State transition back          [PASS]
[10/10] Invalid update arguments       [PASS]
----------------------------------------
Summary
----------------------------------------
Executed : 10/10
Passed   : 10/10 (100%)
Failed   : 0/10 (0%)
========================================
```

### Clean

```bash
make clean
```

Expected output:

```text
[debounce] $ make clean
CLEAN   build artifacts
```

---

## Project Structure

```text
debounce/
├── debounce.c
├── debounce.h
├── debounce_test.c
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

These compiler options help detect common C programming errors and encourage a strict coding style.

---

## Complexity

Each call to `debounce_update()` performs a constant amount of work.

```text
Time complexity:  O(1)
Space complexity: O(1)
```

No memory allocation is performed during runtime.

---

## Limitations

This module assumes:

- The input is binary (`0U` or `1U`).
- `debounce_update()` is called periodically.
- The caller controls the sampling interval.

The module does not provide:

- GPIO configuration.
- Hardware timer configuration.
- Button event generation.
- Rising-edge detection.
- Falling-edge detection.
- Long-press detection.
- Short-press detection.
- Analog filtering.
- Interrupt handling.

These responsibilities can be implemented by higher-level modules.

---

## Design Goals

The main design goals are:

1. Keep the API small.
2. Keep the debounce algorithm deterministic.
3. Make timing behavior explicit through the sampling model.
4. Separate hardware access from signal processing.
5. Make invalid input handling explicit.
6. Avoid dynamic memory allocation.
7. Keep the module easy to unit test.
8. Make the module reusable in larger embedded drivers.

---

## Scope

The goal of this module is to provide a reusable digital-input debounce primitive.

It is intentionally independent of any specific MCU, GPIO peripheral, timer, RTOS, or hardware abstraction layer.

Higher-level modules can build additional functionality such as button events, edge detection, and long-press detection on top of the debounced state.