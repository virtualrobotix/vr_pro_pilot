# VRP-SDD-AP_TECS — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_TECS` |
| LLRD | [`VRP-LLRD-AP_TECS.yaml`](VRP-LLRD-AP_TECS.yaml) |
| DAL | B |
| Status | partial |
| Phase | 4 |

## 1. Purpose

Clean-room BSD design for `VRP_TECS`, functional parity with ArduPilot `AP_TECS`.

## 2. Architecture

Baseline implementation present; integrated via `LibraryCore::tick()`. Roadmap phase **4** per `docs/CERTIFICATION_ROADMAP.md`.

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
| `VRP_TECS::init(double target_alt_m, double target_speed_m_s)` | Public API |
| `VRP_TECS::update(double alt_m, double speed_m_s, double dt_s)` | Public API |

## 6. Verification

Tests: see LLRD `tests:` field and phase runner `test/libraries/run_phase4_tests.py`.
SVCP target: `test/libraries/VRP_TECS/`
