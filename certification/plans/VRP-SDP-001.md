# VRP-SDP-001 — Software Development Plan

## Standards

- C++17, CMake 3.16+
- Coding: `docs/CODING_STANDARDS.md`
- Architecture: `docs/ARCHITECTURE.md`

## Module development order

1. HAL + middleware (phase 0)
2. SafetyCore + sensors (phase 1)
3. Control + navigation (phases 4–8)
4. CopterCore integration (ArduCopter parity)
5. Surface vehicles (rover/boat/sailboat)
6. LibraryCore long tail (phases 9–20)

## Design before code (DAL B)

SDD approval required before merge for DAL B libraries (see `LIBRARY_CERTIFICATION.md`).
