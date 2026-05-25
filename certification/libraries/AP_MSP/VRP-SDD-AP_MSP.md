# VRP-SDD-AP_MSP — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_MSP` |
| LLRD | [`VRP-LLRD-AP_MSP.yaml`](VRP-LLRD-AP_MSP.yaml) |
| DAL | E |
| Status | partial |
| Phase | 9 |

## 1. Purpose

Clean-room BSD design for `VRP_MSP`, functional parity with ArduPilot `AP_MSP`.

## 2. Architecture

Baseline implementation present; integrated via `LibraryCore::tick()`. Roadmap phase **9** per `docs/CERTIFICATION_ROADMAP.md`.

## 3. Data flow

Integrated through `LibraryCore` uORB `aux/*` telemetry unless promoted to vehicle core.
HAL boundary: `src/hal/` for board-specific I/O.

## 4. Safety constraints (DAL E)

- Smoke tests
- Best-effort review

No safety effect — best-effort tests.

## 5. Interface summary

| API | Description |
|---|---|
| `VRP_MSP::init()` | Public API |
| `VRP_MSP::update(const Attitude &att, const LocalPosition &pos, const BatteryStatus &batt, uint64_t time_ms)` | Public API |

## 6. Verification

Tests: see LLRD `tests:` field and phase runner `test/libraries/run_phase9_tests.py`.
SVCP target: `test/libraries/VRP_MSP/`
