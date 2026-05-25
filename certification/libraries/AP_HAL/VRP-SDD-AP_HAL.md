# VRP-SDD-AP_HAL — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_HAL` |
| LLRD | [`VRP-LLRD-AP_HAL.yaml`](VRP-LLRD-AP_HAL.yaml) |
| DAL | B |
| Status | present |
| Phase | 0 |

## 1. Purpose

Clean-room BSD design for `VRP_HAL`, functional parity with ArduPilot `AP_HAL`.

## 2. Architecture

Scaffold for future phase. Roadmap phase **0** per `docs/CERTIFICATION_ROADMAP.md`.

## 3. Data flow

Integrated through `LibraryCore` uORB `aux/*` telemetry unless promoted to vehicle core.
HAL boundary: `src/hal/` for board-specific I/O.

## 4. Safety constraints (DAL B)

- MC/DC on safety paths
- No dynamic heap
- Bounded WCET
- MISRA subset

Hazardous failure — MC/DC on safety paths, no heap, bounded WCET.

## 5. Interface summary

| API | Description |
|---|---|
| `VRP_HAL::init()` | Module initialization |
| `VRP_HAL::update()` | Periodic update |

## 6. Verification

Tests: see LLRD `tests:` field and phase runner `test/libraries/run_phase0_tests.py`.
SVCP target: `test/libraries/VRP_HAL/`
