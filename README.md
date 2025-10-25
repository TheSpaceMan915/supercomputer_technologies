# supercomputer-technologies

A minimal **CMake 3.8.2** parent/child project. The parent aggregates one child: `assignments/assignment1`.

The child computes **π** using the **midpoint rule**:
\[
\pi \approx \frac{1}{n}\sum_{i=1}^{n}\frac{4}{1+\left(\frac{i-0.5}{n}\right)^2}
\]
It logs the workflow (start → parsed `n` → compute → π value → absolute error vs `M_PI` → elapsed → done) and includes **Unity** (vendored) unit tests. The code is strictly **C++98**.

## Build (parent, out-of-source)
```bash
cmake -S . -B build
cmake --build build
```

## Run
```bash
# Linux/macOS:
./build/assignments/assignment1/assignment1 100000
# Windows (MSVC/MinGW; path may vary by generator/config):
.uildssignmentsssignment1ssignment1.exe 100000
```

## Tests
```bash
ctest --test-dir build --output-on-failure
```

## Standalone child build
```bash
cmake -S assignments/assignment1 -B build-assignment1
cmake --build build-assignment1
ctest --test-dir build-assignment1 --output-on-failure
./build-assignment1/assignment1 100000
```

### Sample output
```
[INFO] assignment1 start
[INFO] Parsed n = 100000
[INFO] π ≈ 3.1415926537
[INFO] abs error vs M_PI = 0.0000000001
[INFO] elapsed = 0.120 s
[INFO] assignment1 done
```

### Notes
- **C++98** only; no C++11+ features.
- Windows: `_USE_MATH_DEFINES` is defined before `<cmath>` so `M_PI` is available; a fallback `#define M_PI` is provided if needed.
- Unity is vendored and compiled as C; the C++ test wraps its header in `extern "C"`.
