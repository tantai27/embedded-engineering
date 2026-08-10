# Ring Buffer

## Overview

This module implements a fixed-size byte ring buffer for embedded software.

The purpose of the exercise is to practice a common circular-buffer pattern used
in embedded systems for data streams such as UART, communication interfaces,
drivers, and producer-consumer data paths.

The implementation is expected to:

- Initialize a fixed-size ring buffer with externally provided storage.
- Add (`push`) one byte to the buffer.
- Remove (`pop`) one byte from the buffer.
- Automatically wrap read and write indices when reaching the buffer boundary.
- Detect full and empty buffer conditions.
- Validate all input arguments before accessing memory.
- Maintain buffer state explicitly through read index, write index, and element count.
- Avoid dynamic memory allocation.
- Provide explicit status reporting for each operation.
- Follow defensive programming and clean Embedded C coding practices.

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

