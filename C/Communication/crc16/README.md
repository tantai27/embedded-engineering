# CRC-16

## Overview

This module implements a CRC-16 checksum calculation for a byte array.

The purpose of the exercise is to practice a commonly used data-integrity
mechanism in embedded communication systems and extend the CRC knowledge
introduced by the CRC-8 module.

The implementation uses the CRC-16/IBM algorithm with the following parameters:

- Polynomial: `0x8005`
- Initial value: `0x0000`
- Input reflection: Enabled
- Output reflection: Enabled
- Final XOR value: `0x0000`

The reflected implementation uses the reversed polynomial:

```text
0xA001
```

The implementation is expected to:

- Calculate a CRC-16 value from an input byte array.
- Process the input data byte by byte and bit by bit.
- Validate input pointers before accessing memory.
- Keep the input data read-only.
- Store the calculated CRC through an output pointer.
- Return an explicit status code.
- Use fixed-width integer types suitable for embedded systems.
- Avoid dynamic memory allocation.
- Follow defensive programming and clean Embedded C coding practices.

The module should provide a small, reusable API suitable for communication
software, protocol payloads and other embedded applications requiring
data-integrity verification.

---

## Project Structure

```text
crc16/
├── crc16.c
└── crc16.h
```