# VRP-SDD-AP_CRSF — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_CRSF` |
| LLRD | [`VRP-LLRD-AP_CRSF.yaml`](VRP-LLRD-AP_CRSF.yaml) |
| DAL | E |
| Status | partial |
| Phase | 11 |

## 1. Purpose

Clean-room BSD design for `VRP_CRSF`, functional parity with ArduPilot `AP_CRSF`.

## 2. Architecture

Baseline implementation present; integrated via `LibraryCore::tick()`. Roadmap phase **11** per `docs/CERTIFICATION_ROADMAP.md`.

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
| `VRP_CRSF::init()` | Public API |
| `VRP_CRSF::update(const Attitude &att, const BatteryStatus &batt, const RssiSample &rssi, uint64_t time_ms)` | Public API |

## 6. Verification

Tests: see LLRD `tests:` field and phase runner `test/libraries/run_phase11_tests.py`.
SVCP target: `test/libraries/VRP_CRSF/`
