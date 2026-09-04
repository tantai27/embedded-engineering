# Event Flags

A lightweight Embedded C event flags module that provides a software mechanism for storing and checking multiple event states using a 32-bit bitmask.

The module models a common embedded and RTOS concept where individual bits represent independent events or conditions.

The module provides operations to:

- Initialize the event flags.
- Set one or more event flags.
- Clear one or more event flags.
- Read the current event flag state.
- Check whether all requested event flags are set.

The implementation is hardware-independent and does not require an RTOS or dynamic memory allocation.

The module is designed to practice bitmask-based state management, event-driven programming concepts, defensive Embedded C programming, fixed-width integer types, and explicit status handling.