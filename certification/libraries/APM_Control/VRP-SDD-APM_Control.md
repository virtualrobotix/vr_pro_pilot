# VRP-SDD-APM_Control — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_APM_Control` |
| LLRD | [`VRP-LLRD-APM_Control.yaml`](VRP-LLRD-APM_Control.yaml) |
| DAL | B |
| Status | partial |
| Phase | 5 |

## 1. Purpose

Clean-room BSD design for `VRP_APM_Control`, functional parity with ArduPilot `APM_Control`.

## 2. Architecture

Baseline implementation present; integrated via `LibraryCore::tick()`. Roadmap phase **5** per `docs/CERTIFICATION_ROADMAP.md`.

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
| `VRP_APM_Control::init()` | Public API |
| `VRP_APM_Control::update(const Attitude &attitude, const FwNavSetpoint &nav, const FwControlSetpoint &tecs_sp,
                           double dt_s)` | Public API |

## 6. Verification

Tests: see LLRD `tests:` field and phase runner `test/libraries/run_phase5_tests.py`.
SVCP target: `test/libraries/VRP_APM_Control/`
