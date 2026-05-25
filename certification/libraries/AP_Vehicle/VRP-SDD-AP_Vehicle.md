# VRP-SDD-AP_Vehicle — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_Vehicle` |
| LLRD | [`VRP-LLRD-AP_Vehicle.yaml`](VRP-LLRD-AP_Vehicle.yaml) |
| DAL | B |
| Status | partial |
| Phase | 0 |

## 1. Purpose

Clean-room BSD design for `VRP_Vehicle`, functional parity with ArduPilot `AP_Vehicle`.

## 2. Architecture

Baseline implementation present; integrated via `LibraryCore::tick()`. Roadmap phase **0** per `docs/CERTIFICATION_ROADMAP.md`.

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
| `VRP_Vehicle::make_vehicle(const std::string &kind, UORB &uorb, VRPParamStore &params)` | Public API |

## 6. Verification

Tests: see LLRD `tests:` field and phase runner `test/libraries/run_phase0_tests.py`.
SVCP target: `test/libraries/VRP_Vehicle/`
