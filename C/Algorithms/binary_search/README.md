# Binary Search

## Description

This module implements a safe Binary Search API for searching a value in an ascending sorted array.

The implementation is designed following common Embedded C and Automotive software practices, with emphasis on correctness, robustness and defensive programming rather than simply implementing the algorithm.

The implementation is expected to:

- Search for a target value in an ascending sorted array.
- Return both execution status and the found index through an output parameter.
- Validate all input arguments before accessing memory.
- Prevent unsigned integer overflow when calculating the middle index.
- Prevent unsigned underflow during boundary updates.
- Follow a defensive programming approach suitable for safety-critical software.
- Provide a simple, reusable API with explicit status reporting.