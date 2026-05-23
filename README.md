# Barnsley Fern Renderer

Generates Barnsley's Fern by iteratively applying one of four affine transformations (selected with weighted probabilities matching the classic fractal recipe) to a moving point, then renders the result as ASCII art. Pixels are stored as a packed 1-bit bitmap to keep memory usage tiny, and the final image is printed to standard output as a 128x48 grid of `#` and space characters.

## What's in here

- `fern.cpp` — main program: iteration loop, transform selection, bit-packed pixel storage, and ASCII renderer
- `CMakeLists.txt` — build configuration

## Requirements

- C++17 toolchain (GCC 9+, Clang 10+, or MSVC 2019+)
- CMake 3.20+

## How to build & run

```bash
cmake -B build
cmake --build build
./build/CS_3505-001_Spring_2026_Assignment_1__Barnsley_fern
```

In CLion: open the folder, CLion detects `CMakeLists.txt` and configures the project. Pick the target from the run-config dropdown and click the play button.

## How to use

When launched, the program prompts on stdin for the number of iterations. Provide a positive integer — the higher the count, the denser and more detailed the rendered fern. The fern is then printed to stdout. A few thousand iterations produces a recognizable silhouette; tens of thousands fills in the fronds nicely.

## Origin

Originally a coursework assignment; pulled out as a standalone repo.
