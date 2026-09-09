# Cache-Aligned Lock-Free SPSC Queue

This project is a high-performance, lock-free Single-Producer Single-Consumer
(SPSC) ring buffer written in C++20. It is designed to act as a core component
for systems requiring ultra-low latency and zero-allocation data streaming.

## Project Goals

- Provide a lock-free synchronization mechanism without OS-level context
  switches.
- Ensure deterministic performance for hot-path systems.
- Serve as a foundation for a zero-copy market data parser.

## Technical Specifications

- **Time Complexity:** O(1) for push and pop operations.
- **Space Complexity:** O(N) where N is the fixed capacity.
- **Concurrency:** Thread-safe for one producer and one consumer operating
  simultaneously.
- **Memory Optimizations:**
  - Cache-line aligned to prevent false sharing between CPU cores.
  - Zero heap allocations during the operational lifecycle.
  - Optimized indexing mechanisms for wrapping bounds.
- **Type Safety:** Enforces trivial copyability for queue elements.

## Build and Run

To build the project and run the provided test harness:

```bash
make
./main
```
