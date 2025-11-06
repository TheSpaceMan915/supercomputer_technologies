# supercomputer-technologies

Modernized, pedagogy‑first C++ assignments built with **CMake 3.8.2** and **C++98**.  
Each assignment is an independent child project you can build **standalone** or via the **parent** (recommended).
Code favors clarity, RAII, and the C++ Core Guidelines (as applicable to C++98).

## What’s inside
- `assignments/assignment1` — π approximation via the **midpoint rule** (serial, C++98).
- `assignments/assignment2` — Dense **N×N matrix multiply** `C = A·B` (double, triple loop).
- `assignments/assignment3-task1` — π via midpoint with **OpenMP** reduction (C++98, OpenMP 3.0).

Each child provides:
- A small static core library (pure computation, no I/O).
- A CLI executable (parsing, logging, timing).
- Unity-based unit tests wired through **CTest** (vendored minimal Unity).

## Requirements
- **CMake ≥ 3.8.2**
- A C++98 compiler: GCC, Clang, or MSVC
- For Assignment 3 (OpenMP):
  - GCC/Clang with OpenMP support installed
  - MSVC with `/openmp` available (CMake wiring handles flags; see notes below)

## Quick start — build everything (parent)
```bash
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

Example runs (after parent build):
```bash
# Assignment 1 — midpoint π (serial)
./build/assignments/assignment1/assignment1 100000

# Assignment 2 — matrix multiply (double)
./build/assignments/assignment2/assignment2 512

# Assignment 3 — midpoint π (OpenMP)
OMP_NUM_THREADS=8 ./build/assignments/assignment3-task1/assignment3-task1 1000000
```

### Windows (MSVC) notes
- Use the "x64 Native Tools Command Prompt for VS".
- Configure & build the same way:
  ```bat
  cmake -S . -B build
  cmake --build build
  .\build\assignments\assignment3-task1\assignment3-task1.exe 1000000
  ```
- OpenMP: the build system adds `/openmp` automatically when the OpenMP package is found.

## Build a single child (standalone)
```bash
# Assignment 1
cmake -S assignments/assignment1 -B build-a1
cmake --build build-a1
./build-a1/assignment1 100000

# Assignment 2
cmake -S assignments/assignment2 -B build-a2
cmake --build build-a2
./build-a2/assignment2 512

# Assignment 3 (OpenMP)
cmake -S assignments/assignment3-task1 -B build-a3
cmake --build build-a3
OMP_NUM_THREADS=8 ./build-a3/assignment3-task1 1000000
```

## What each assignment demonstrates

### Assignment 1 — π via midpoint (serial)
- Formula: \( \pi \approx \tfrac{1}{n} \sum_{i=1}^n \tfrac{4}{1 + ((i - 0.5)/n)^2} \)  
- Separation of concerns: pure compute vs CLI/logging
- CTest‑driven unit test verifying error \(< 1\times10^{-5}\) for large `n`

### Assignment 2 — dense matrix multiply
- Initialization: `A[i][j] = i + 1`, `B[i][j] = 1.0 / (j + 1)` (0‑based)
- Contiguous 1‑D storage (`std::vector<double>`) with index `i*N + j`
- Logs boundary elements and simple performance metrics (ms, FLOPS, GFLOPS)

### Assignment 3 — π via midpoint with OpenMP
- OpenMP 3.0 `reduction(+:sum)` over the main loop
- Uses `omp_get_wtime()` when available (falls back to `std::clock()`)
- Logs `threads`, `pi`, absolute error vs `M_PI`, and elapsed ms

## Out‑of‑source builds
Always build outside the source tree to keep the repo clean:
```bash
cmake -S . -B build
```
A `.gitignore` entry for `build/` is recommended.

## Platform/portability notes
- Standard: **C++98** (no C++11 features).
- Warnings: GCC/Clang `-Wall -Wextra -Wpedantic`; MSVC `/W4`; no `-Werror` by default.
- Windows: ensure `_USE_MATH_DEFINES` is defined before `<cmath>` so `M_PI` is available.
- OpenMP: if your toolchain lacks OpenMP, Assignment 3’s parallel function falls back to the serial loop
  (build still succeeds; performance won’t scale).

## Troubleshooting
- **CMake can’t find OpenMP**: install your compiler’s OpenMP runtime (`libgomp`/`libomp`) or enable `/openmp` on MSVC.
- **Link errors for OpenMP**: ensure you’re using the same compiler for all steps; clear `build/` and reconfigure.
- **Very large N**: Assignments include conservative guards (time/memory) and will emit friendly errors.

---

© 2025. For learning and experimentation. Replace or augment with your preferred license.
