# Insertion Sort

A simple Embedded C implementation of the Insertion Sort algorithm for
sorting an array of 32-bit unsigned integers in ascending order.

## Overview

Insertion Sort builds the sorted portion of an array one element at a time.

For each element, the implementation moves larger elements in the already
sorted portion one position to the right and inserts the current element
into its correct position.

The module operates directly on the caller-provided array and does not use
dynamic memory allocation.

## Scope

This module focuses on:

- Insertion Sort algorithm
- In-place array sorting
- Sorted and unsorted array regions
- Element shifting and insertion
- Defensive argument validation
- Unit-testable Embedded C implementation
- Predictable memory usage