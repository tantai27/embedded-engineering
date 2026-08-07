# Memory Copy

## Description

This module implements a safe API to copy a memory block from a source buffer to a destination buffer.

The implementation is designed following common Embedded C and Automotive software practices, with emphasis on robustness, defensive programming and predictable behavior.

The implementation is expected to:

- Copy an arbitrary number of bytes from the source buffer to the destination buffer.
- Validate all input arguments before accessing memory.
- Safely handle overlapping memory regions.
- Preserve source data integrity throughout the copy operation.
- Provide a simple, reusable API with explicit status reporting.