# Computer Architecture Assignment 3

## Overview

This repository contains my implementation of three tasks for the Computer Architecture course, focusing on cache simulation, fast matrix multiplication, and binary patching.

## Contents

### 1. Cache Simulation (`cache/`)
- **Description**: Simulates a cache memory system using the Least Frequently Used (LFU) replacement policy.
- **Main Features**:
  - Structs for cache lines and sets.
  - Functions to initialize a cache, read a byte, and write a byte.
  - Write-through policy for memory updates.
- **How to Run**: Includes a Makefile for compiling the code into an executable called `cache`.

### 2. Fast Matrix Multiplication (`FMM/`)
- **Description**: Optimized matrix multiplication implementation.
- **Main Features**:
  - Efficient algorithm for multiplying two square matrices.
  - Input/output of matrices through file paths.
- **How to Run**: The directory contains a Makefile to compile the program into an executable named `fmm`.

### 3. Binary Patching (`patchwork`)
- **Description**: A binary reverse-engineered to reveal a secret flag.
- **Files**: Includes the patched binary and a report detailing the steps taken for reverse engineering.
  
## How to Compile and Run

1. Navigate to the respective task directory (`cache/` or `FMM/`).
2. Run `make` to compile the code.
3. Execute the binary (`cache` or `fmm`).

