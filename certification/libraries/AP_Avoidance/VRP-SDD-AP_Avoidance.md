# VRP-SDD-AP_Avoidance — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_Avoidance` |
| LLRD | [`VRP-LLRD-AP_Avoidance.yaml`](VRP-LLRD-AP_Avoidance.yaml) |
| DAL | B |
| Status | partial |
| Phase | 19 |

## 1. Purpose

Clean-room BSD design for `VRP_Avoidance`, functional parity with ArduPilot `AP_Avoidance`.

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
| `VRP_Avoidance::init()` | Public API |
| `VRP_Avoidance::update(bool armed, float prox_min_m)` | Public API |
| `VRP_Avoidance::format_ap_avoidance(const ApAvoidanceState &s)` | Public API |

## 6. Verification

Tests: see LLRD `tests:` field and phase runner `test/libraries/run_phase19_tests.py`.
SVCP target: `test/libraries/VRP_Avoidance/`
