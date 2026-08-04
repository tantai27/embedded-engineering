# String Length

## Description

This module implements a safe API to calculate the length of a null-terminated string.

The implementation is designed following common Embedded C and Automotive software practices, with emphasis on robustness rather than simply reproducing the behavior of the standard library.

The implementation is expected to:

- Calculate the number of characters before the null terminator (`'\0'`).
- Validate all input arguments before accessing memory.
- Protect against integer overflow during length accumulation.
- Follow a defensive programming approach suitable for safety-critical software.
- Provide a simple, reusable API with explicit status reporting.