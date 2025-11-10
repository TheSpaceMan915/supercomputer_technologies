# supercomputer-technologies

A small collection of self-contained C++98 assignments for numerical computing,
performance experiments, and OpenMP practice. All projects are designed for
out-of-source builds using CMake ≥ 3.8.2 and standard toolchains (GCC, Clang,
MSVC), with simple console interfaces and Unity-based unit tests where needed.

## Layout

- `assignments/assignment1` — Midpoint rule approximation of π (C++98).
- `assignments/assignment2` — N×N dense matrix multiplication baseline.
- `assignments/assignment3-task1` — Midpoint rule π with OpenMP 3.0 (parallel).
- `assignments/assignment3-task2` — N×N matrix multiply with OpenMP 3.0 (parallel).

Each child is a standalone CMake project:
you can build via the parent or directly in the child directory.

## Requirements

- CMake ≥ 3.8.2
- A C++ compiler with C++98 support:
  - GCC, Clang, or MSVC (tested configurations).
- Optional:
  - OpenMP 3.0+ (for `assignment3-task1` and `assignment3-task2`).
- Recommended:
  - Out-of-source builds (no `build/` inside source tree).

## Build (parent, all assignments)

From the repository root:

```bash
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

This configures and builds all child projects and runs their tests.

## Build & Run (per assignment)

### Assignment 1 — π via Midpoint (C++98)

```bash
cmake -S assignments/assignment1 -B build-a1
cmake --build build-a1
./build-a1/assignment1 1000000
```

Logs the approximation of π, error vs `M_PI`, and timing.

### Assignment 2 — Matrix Multiplication Baseline

```bash
cmake -S assignments/assignment2 -B build-a2
cmake --build build-a2
./build-a2/assignment2 512
```

Computes `C = A · B` with:
- `A[i][j] = i + 1`
- `B[i][j] = 1.0 / (j + 1)`
and reports boundary elements and FLOPS for the naive triple-loop algorithm.

### Assignment 3 — Task 1: π with OpenMP

```bash
cmake -S assignments/assignment3-task1 -B build-a3t1
cmake --build build-a3t1
./build-a3t1/assignment3-task1 1000000
```

Uses OpenMP 3.0 (if available) to parallelize the midpoint sum:
- Logs `n`, thread count, π, absolute error vs `M_PI`, and elapsed time.
- Falls back to a serial implementation when built without OpenMP flags.

### Assignment 3 — Task 2: Parallel Matrix Multiply

```bash
cmake -S assignments/assignment3-task2 -B build-a3t2
cmake --build build-a3t2
./build-a3t2/assignment3-task2 512
```

Performs N×N matrix multiply with:
- `A[i][j] = i + 1`
- `B[i][j] = 1.0 / (j + 1)`
- `C = A · B` via the naive triple-loop kernel

and logs:

- Mode (`serial` or `parallel` with OpenMP and thread count)
- Boundary elements:
  `C[0][0]`, `C[0][N-1]`, `C[N-1][0]`, `C[N-1][N-1]`
- `elapsed_ms`, `flops = 2·N³`, and `gflops`.

## Notes

- All C++ code is restricted to C++98 (no C++11 features).
- OpenMP is optional: if detection or flags fail, code falls back to serial paths.
- Builds are intended to be warning-clean with:
  - GCC/Clang: `-Wall -Wextra -Wpedantic`
  - MSVC: `/W4`
- Use out-of-source build directories (e.g. `build/`, `build-a1/`) to keep the tree clean.
