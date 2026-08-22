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
├── queue.c
└── queue.h
```