# VRP-SDD-AP_DAL — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_DAL` |
| LLRD | [`VRP-LLRD-AP_DAL.yaml`](VRP-LLRD-AP_DAL.yaml) |
| DAL | B |
| Status | partial |
| Phase | 19 |

## 1. Purpose

Clean-room BSD design for `VRP_DAL`, functional parity with ArduPilot `AP_DAL`.

## 2. Architecture

Baseline implementation present; integrated via `LibraryCore::tick()`. Roadmap phase **19** per `docs/CERTIFICATION_ROADMAP.md`.

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
| `VRP_DAL::init()` | Public API |
| `VRP_DAL::format_dal(const DalState &s)` | Public API |

## 6. Verification

Tests: see LLRD `tests:` field and phase runner `test/libraries/run_phase19_tests.py`.
SVCP target: `test/libraries/VRP_DAL/`
