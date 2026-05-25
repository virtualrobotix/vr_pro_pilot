# VRP-SDD-AP_AccelCal — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_AccelCal` |
| LLRD | [`VRP-LLRD-AP_AccelCal.yaml`](VRP-LLRD-AP_AccelCal.yaml) |
| DAL | C |
| Status | partial |
| Phase | 19 |

## 1. Purpose

Clean-room BSD design for `VRP_AccelCal`, functional parity with ArduPilot `AP_AccelCal`.

## 2. Architecture

Baseline implementation present; integrated via `LibraryCore::tick()`. Roadmap phase **19** per `docs/CERTIFICATION_ROADMAP.md`.

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
| `VRP_AccelCal::init()` | Public API |
| `VRP_AccelCal::update(bool armed, uint64_t tick)` | Public API |
| `VRP_AccelCal::format_accel_cal(const AccelCalState &s)` | Public API |

## 6. Verification

Tests: see LLRD `tests:` field and phase runner `test/libraries/run_phase19_tests.py`.
SVCP target: `test/libraries/VRP_AccelCal/`
