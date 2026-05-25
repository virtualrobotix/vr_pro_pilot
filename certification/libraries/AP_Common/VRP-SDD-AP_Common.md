# VRP-SDD-AP_Common — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_Common` |
| LLRD | [`VRP-LLRD-AP_Common.yaml`](VRP-LLRD-AP_Common.yaml) |
| DAL | B |
| Status | partial |
| Phase | 1 |

## 1. Purpose

Clean-room BSD design for `VRP_Common`, functional parity with ArduPilot `AP_Common`.

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
| `VRP_Common::format_wpnav(const WpNavOutput &n)` | Public API |
| `VRP_Common::format_motors_quad(const MotorOutputQuad &m)` | Public API |
| `VRP_Common::format_imu(const ImuSample &s)` | Public API |
| `VRP_Common::is_ar_surface_vehicle(const std::string &vehicle)` | Public API |

## 6. Verification

Tests: see LLRD `tests:` field and phase runner `test/libraries/run_phase1_tests.py`.
SVCP target: `test/libraries/VRP_Common/`
