# VRP-SDD-AP_Airspeed — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_Airspeed` |
| LLRD | [`VRP-LLRD-AP_Airspeed.yaml`](VRP-LLRD-AP_Airspeed.yaml) |
| DAL | C |
| Status | partial |
| Phase | 11 |

## 1. Purpose

Clean-room BSD design for `VRP_Airspeed`, functional parity with ArduPilot `AP_Airspeed`.

## 2. Architecture

Baseline implementation present; integrated via `LibraryCore::tick()`. Roadmap phase **11** per `docs/CERTIFICATION_ROADMAP.md`.

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
| `VRP_Airspeed::init()` | Public API |
| `VRP_Airspeed::update(double ground_speed_m_s, uint64_t time_us)` | Public API |
| `VRP_Airspeed::format_airspeed(const AirspeedSample &s)` | Public API |

## 6. Verification

Tests: see LLRD `tests:` field and phase runner `test/libraries/run_phase11_tests.py`.
SVCP target: `test/libraries/VRP_Airspeed/`
