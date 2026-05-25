# VRP-SDD-AP_L1_Control — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_L1_Control` |
| LLRD | [`VRP-LLRD-AP_L1_Control.yaml`](VRP-LLRD-AP_L1_Control.yaml) |
| DAL | B |
| Status | partial |
| Phase | 6 |

## 1. Purpose

Clean-room BSD design for `VRP_L1_Control`, functional parity with ArduPilot `AP_L1_Control`.

## 2. Architecture

Baseline implementation present; integrated via `LibraryCore::tick()`. Roadmap phase **6** per `docs/CERTIFICATION_ROADMAP.md`.

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
| `VRP_L1_Control::init(double period_s = 25.0, double damping = 0.75)` | Public API |
| `VRP_L1_Control::update(const LocalPosition &pos, const Waypoint &from, const Waypoint &to, double dt_s)` | Public API |
| `VRP_L1_Control::format_l1(const L1Output &out)` | Public API |

## 6. Verification

Tests: see LLRD `tests:` field and phase runner `test/libraries/run_phase6_tests.py`.
SVCP target: `test/libraries/VRP_L1_Control/`
