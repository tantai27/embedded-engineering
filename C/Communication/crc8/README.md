# CRC-8

## Overview

This module implements a CRC-8 checksum calculation for a byte array.

The exercise focuses on implementing a common data-integrity mechanism used in
embedded communication systems to detect accidental data corruption during
transmission or storage.

The implementation uses the CRC-8/ITU algorithm with the following parameters:

- Polynomial: `0x07`
- Initial value: `0x00`
- Input reflection: Disabled
- Output reflection: Disabled
- Final XOR value: `0x00`

The implementation is expected to:

- Calculate a CRC-8 value from an input byte array.
- Process the input data byte by byte and bit by bit.
- Validate input pointers before accessing memory.
- Keep the input data read-only.
- Return an explicit status code.
- Store the calculated CRC through an output pointer.
- Use fixed-width integer types suitable for embedded systems.
- Follow defensive programming and clean Embedded C coding practices.
- Avoid dynamic memory allocation.

The module should provide a small, reusable API suitable for communication
software and other embedded applications requiring basic data-integrity
verification.

---

## Project Structure

```text
crc8/
├── README.md
├── crc8.c
└── crc8.h