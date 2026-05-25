# VRP-SDD-AP_LandingGear — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_LandingGear` |
| LLRD | [`VRP-LLRD-AP_LandingGear.yaml`](VRP-LLRD-AP_LandingGear.yaml) |
| DAL | B |
| Status | partial |
| Phase | 9 |

## 1. Purpose

Clean-room BSD design for `VRP_LandingGear`, functional parity with ArduPilot `AP_LandingGear`.

## 2. Architecture

Baseline implementation present; integrated via `LibraryCore::tick()`. Roadmap phase **9** per `docs/CERTIFICATION_ROADMAP.md`.

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
| `VRP_LandingGear::init()` | Public API |
| `VRP_LandingGear::update(bool armed, bool land_mode)` | Public API |

## 6. Verification

Tests: see LLRD `tests:` field and phase runner `test/libraries/run_phase9_tests.py`.
SVCP target: `test/libraries/VRP_LandingGear/`
