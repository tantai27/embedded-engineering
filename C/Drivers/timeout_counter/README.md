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
├── timeout_counter.c
└── timeout_counter.h
```