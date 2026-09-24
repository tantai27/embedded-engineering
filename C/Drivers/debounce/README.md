# Debounce

## Overview

`debounce` is a small Embedded C module for filtering unstable digital input signals such as mechanical buttons and switches.

Mechanical contacts can rapidly alternate between logical states when pressed or released. This behavior, commonly called **switch bounce**, can cause a single physical action to be interpreted as multiple input transitions.

This module accepts a raw digital input sample on each update and changes the reported stable state only after the new input remains unchanged for a configured number of consecutive samples.

---

## Features

- Debounce binary digital input signals.
- Configurable number of stable samples.
- Explicit initialization.
- Explicit status codes.
- Input argument validation.
- No dynamic memory allocation.
- Deterministic state-based behavior.
- Suitable for GPIO/button driver integration.

---

## Design

The module uses a consecutive-sample approach.

```text
Raw input
   │
   ▼
┌─────────────────────┐
│     Debounce        │
│                     │
│ Candidate state     │
│ Consecutive samples │
│ Stable state        │
└──────────┬──────────┘
           │
           ▼
     Stable output
```

When the raw input changes, it becomes a candidate state.

The candidate must remain unchanged for the configured number of consecutive updates before it becomes the new stable state.

For example, with:

```text
stable_ticks = 3
```

an input transition such as:

```text
Raw:     0 0 1 0 1 1 1 1
Stable:  0 0 0 0 0 0 1 1
```

shows that the short transitions caused by bouncing are ignored. The new state is accepted only after three consecutive samples of `1`.

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

Parameters:

- `debounce`: pointer to the debounce state.
- `initial_state`: initial stable input state.
- `stable_ticks`: number of consecutive samples required to accept a new state.

`stable_ticks` must be greater than zero.

---

### `debounce_update()`

```c
debounce_status_t debounce_update(
    debounce_t * const debounce,
    uint8_t raw_state,
    uint8_t * const stable_state);
```

Updates the debounce state using one raw input sample.

The stable output changes only after the candidate state has remained unchanged for the configured number of consecutive updates.

---

## Status Codes

The module returns:

```c
typedef enum
{
    DEBOUNCE_STATUS_SUCCESS = 0U,
    DEBOUNCE_STATUS_INVALID_ARGUMENT
} debounce_status_t;
```

`DEBOUNCE_STATUS_INVALID_ARGUMENT` is returned when:

- The debounce object is `NULL`.
- The output pointer is `NULL`.
- `stable_ticks` is zero.
- A state value other than `0U` or `1U` is provided.

---

## State

Each debounce instance stores:

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

The counter saturates at `stable_ticks`.

### `stable_state`

The currently accepted and debounced state.

### `candidate_state`

The raw state currently being evaluated for acceptance.

---

## Design Considerations

The module intentionally does not contain any hardware-specific timer or GPIO code.

`debounce_update()` is expected to be called periodically by a higher-level component.

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

This keeps the debounce algorithm independent from the underlying MCU, GPIO driver, RTOS, or timer implementation.

---

## Embedded C Considerations

The implementation is designed with embedded software practices in mind:

- Fixed-width integer types.
- No dynamic memory allocation.
- Explicit initialization.
- Explicit status handling.
- Defensive pointer validation.
- No global mutable state.
- Deterministic execution.
- Saturating counter behavior.
- Hardware-independent core logic.

The module can therefore be integrated into bare-metal firmware, RTOS-based applications, or a higher-level GPIO driver.

---

## Applications

Typical applications include:

- Mechanical push buttons.
- Toggle switches.
- GPIO input filtering.
- User-interface buttons.
- Digital control inputs.
- Embedded control panels.

---

## Limitations

This module assumes:

- The input is binary (`0U` or `1U`).
- `debounce_update()` is called at a reasonably consistent interval.
- The caller provides the sampling period.

The module does not:

- Configure GPIO hardware.
- Read MCU registers directly.
- Provide a timer.
- Detect long presses.
- Detect short presses.
- Generate rising/falling-edge events.
- Handle analog signal filtering.

These responsibilities can be implemented by higher-level modules.

---

## Complexity

Each call to `debounce_update()` performs a constant amount of work.

```text
Time complexity:  O(1)
Space complexity: O(1)
```

No memory allocation is performed during runtime.

---

## Scope

The goal of this module is to provide a small, reusable debounce primitive rather than a complete button driver.

Higher-level functionality such as edge detection, button events, long-press detection, and GPIO abstraction can be built on top of the debounced state.