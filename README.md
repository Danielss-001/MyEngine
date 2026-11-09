
# MyEngine

A 3D game engine built from scratch in C++20, focused on graphics programming, hardware-aware engineering, and clean software architecture.

> **Status:** Early development — platform layer and rendering foundation.

## Project vision

MyEngine is a learning-driven 3D engine project. Its goal is to explore the complete path from application architecture and memory management to GPU rendering, shader programming, and parallel workloads.

The project prioritizes understanding how systems work, measuring performance, and documenting engineering decisions instead of relying on opaque abstractions.

## Technology stack

- **Language:** C++20
- **Build system:** CMake
- **Build generator:** Ninja
- **Compiler:** Clang
- **Platform and input:** SDL3
- **Graphics and compute:** SDL_GPU
- **Version control:** Git and GitHub

## Current development goals

- [ ] Establish a reproducible Windows development environment.
- [ ] Integrate SDL3 through CMake.
- [ ] Implement the platform layer: window, events, keyboard, and mouse.
- [ ] Initialize SDL_GPU and verify the selected graphics backend.
- [ ] Render the first frame and triangle.
- [ ] Introduce shader compilation and resource management.
- [ ] Build a modular rendering architecture.
- [ ] Explore multithreaded workloads and GPU compute.
- [ ] Add tests, profiling, and performance benchmarks.

## Engineering principles

- Understand the cost and responsibility of every abstraction.
- Keep platform-specific code behind explicit boundaries.
- Prefer reproducible builds and small, reviewable changes.
- Measure performance before claiming an optimization.
- Document architectural decisions and failed experiments.
- Distinguish CPU concurrency from GPU execution and synchronization.

## Documentation

The `docs/` directory will contain the architecture overview, technical decisions, learning journal, and graphics programming notes.

The `experiments/` directory will hold isolated tests and benchmarks.

## Development status

This is an educational and experimental project under active development. Features, APIs, and architecture may change as the engine evolves.
