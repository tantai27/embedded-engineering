# Checksum-8

## Overview

This module implements an 8-bit additive checksum calculation for a byte
array.

The purpose of the exercise is to practice a simple data-integrity mechanism
commonly used in embedded communication systems to detect accidental data
corruption during transmission or storage.

The checksum is calculated by summing all input bytes and retaining the
least-significant 8 bits of the result.

The implementation is expected to:

- Calculate an 8-bit checksum from an input byte array.
- Process the input data byte by byte.
- Handle checksum overflow through 8-bit truncation.
- Validate input pointers before accessing memory.
- Keep the input data read-only.
- Store the calculated checksum through an output pointer.
- Return an explicit status code.
- Use fixed-width integer types suitable for embedded systems.
- Avoid dynamic memory allocation.
- Follow defensive programming and clean Embedded C coding practices.

The module should provide a small, reusable API suitable for communication
software and other embedded applications requiring basic data-integrity
verification.

---

## Project Structure

```text
checksum8/
├── checksum8.c
└── checksum8.h
```