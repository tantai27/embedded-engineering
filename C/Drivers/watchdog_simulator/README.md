```markdown
# Watchdog Simulator

A lightweight Embedded C watchdog simulator that models a basic software watchdog using a tick-based timeout mechanism.

The module simulates the core watchdog behavior commonly found in embedded systems:

- Start the watchdog with a configurable timeout.
- Advance elapsed time using periodic ticks.
- Feed the watchdog to reset its elapsed time.
- Detect watchdog expiration when the timeout is reached.
- Stop the watchdog after expiration.

The implementation is hardware-independent and does not require an RTOS or dynamic memory allocation.

The module is designed to practice defensive Embedded C programming, explicit state management, timeout handling, and fixed-width integer types.
```
