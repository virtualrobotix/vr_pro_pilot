# VRP-SDD-PID — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_PID` |
| LLRD | [`VRP-LLRD-PID.yaml`](VRP-LLRD-PID.yaml) |
| DAL | B |
| Status | partial |
| Phase | 1 |

## 1. Purpose

Clean-room BSD design for `VRP_PID`, functional parity with ArduPilot `PID`.

## 2. Architecture

Baseline implementation present; integrated via `LibraryCore::tick()`. Roadmap phase **1** per `docs/CERTIFICATION_ROADMAP.md`.

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
| `VRP_PID::update(double setpoint, double measurement, double dt_s)` | Public API |
| `VRP_PID::reset()` | Public API |

## 6. Verification

Tests: see LLRD `tests:` field and phase runner `test/libraries/run_phase1_tests.py`.
SVCP target: `test/libraries/VRP_PID/`
