# supercomputer-technologies

Parent/child CMake (3.8.2) in **C++98**. Children:
- `assignments/assignment1`: π via midpoint rule.
- `assignments/assignment2`: N×N matrix multiply using triple loop.

## Build (parent)
```bash
cmake -S . -B build && cmake --build build
ctest --test-dir build --output-on-failure
```
## Run
```bash
./build/assignments/assignment1/assignment1 100000
./build/assignments/assignment2/assignment2 512
```