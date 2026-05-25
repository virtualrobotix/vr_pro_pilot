# VRP-SDD-AP_Proximity — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_Proximity` |
| LLRD | [`VRP-LLRD-AP_Proximity.yaml`](VRP-LLRD-AP_Proximity.yaml) |
| DAL | C |
| Status | partial |
| Phase | 8 |

## 1. Purpose

Clean-room BSD design for `VRP_Proximity`, functional parity with ArduPilot `AP_Proximity`.

## 2. Architecture

Baseline implementation present; integrated via `LibraryCore::tick()`. Roadmap phase **8** per `docs/CERTIFICATION_ROADMAP.md`.

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
| `VRP_Proximity::init(double warn_m = 3.0, double fence_radius_m = 25.0)` | Public API |
| `VRP_Proximity::update(double x_m, double y_m, const RangeFinderSample &rng, const AdsbVehicle *adsb = nullptr)` | Public API |
| `VRP_Proximity::format_proximity(const ProximitySample &s)` | Public API |

## 6. Verification

Tests: see LLRD `tests:` field and phase runner `test/libraries/run_phase8_tests.py`.
SVCP target: `test/libraries/VRP_Proximity/`
