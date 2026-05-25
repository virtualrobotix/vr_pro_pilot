# VRP-SDD-AP_Hott_Telem — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_Hott_Telem` |
| LLRD | [`VRP-LLRD-AP_Hott_Telem.yaml`](VRP-LLRD-AP_Hott_Telem.yaml) |
| DAL | E |
| Status | partial |
| Phase | 10 |

## 1. Purpose

Clean-room BSD design for `VRP_Hott_Telem`, functional parity with ArduPilot `AP_Hott_Telem`.

## 2. Architecture

Baseline implementation present; integrated via `LibraryCore::tick()`. Roadmap phase **10** per `docs/CERTIFICATION_ROADMAP.md`.

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
| `VRP_Hott_Telem::init()` | Public API |
| `VRP_Hott_Telem::update(const Attitude &att, const LocalPosition &pos, const BatteryStatus &batt, uint64_t time_ms)` | Public API |

## 6. Verification

Tests: see LLRD `tests:` field and phase runner `test/libraries/run_phase10_tests.py`.
SVCP target: `test/libraries/VRP_Hott_Telem/`
