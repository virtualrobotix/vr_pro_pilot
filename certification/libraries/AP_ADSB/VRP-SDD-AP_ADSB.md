# VRP-SDD-AP_ADSB — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_ADSB` |
| LLRD | [`VRP-LLRD-AP_ADSB.yaml`](VRP-LLRD-AP_ADSB.yaml) |
| DAL | C |
| Status | partial |
| Phase | 10 |

## 1. Purpose

Clean-room BSD design for `VRP_ADSB`, functional parity with ArduPilot `AP_ADSB`.

## 2. Architecture

Baseline implementation present; integrated via `LibraryCore::tick()`. Roadmap phase **10** per `docs/CERTIFICATION_ROADMAP.md`.

## 3. Data flow

Integrated through `LibraryCore` uORB `aux/*` telemetry unless promoted to vehicle core.
HAL boundary: `src/hal/` for board-specific I/O.

## 4. Safety constraints (DAL C)

- Statement coverage 100%
- Requirements-based tests
- Design review

Major failure — requirements + tests + review; structural coverage target 100% statement.

## 5. Interface summary

| API | Description |
|---|---|
| `VRP_ADSB::init(double intruder_x_m = 120.0)` | Public API |
| `VRP_ADSB::set_intruder_x(double x_m)` | Public API |
| `VRP_ADSB::update(uint64_t tick, double own_x_m, double own_y_m, double own_alt_m = 0.0)` | Public API |
| `VRP_ADSB::format_adsb(const AdsbVehicle &v)` | Public API |

## 6. Verification

Tests: see LLRD `tests:` field and phase runner `test/libraries/run_phase10_tests.py`.
SVCP target: `test/libraries/VRP_ADSB/`
