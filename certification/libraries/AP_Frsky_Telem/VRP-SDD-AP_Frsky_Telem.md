# VRP-SDD-AP_Frsky_Telem — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_Frsky_Telem` |
| LLRD | [`VRP-LLRD-AP_Frsky_Telem.yaml`](VRP-LLRD-AP_Frsky_Telem.yaml) |
| DAL | E |
| Status | partial |
| Phase | 8 |

## 1. Purpose

Clean-room BSD design for `VRP_Frsky_Telem`, functional parity with ArduPilot `AP_Frsky_Telem`.

## 2. Architecture

Baseline implementation present; integrated via `LibraryCore::tick()`. Roadmap phase **8** per `docs/CERTIFICATION_ROADMAP.md`.

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
| `VRP_Frsky_Telem::init()` | Public API |
| `VRP_Frsky_Telem::update(const std::string &mode, const Attitude &att, const BatteryStatus &batt,
                     const LocalPosition &pos, uint64_t time_ms)` | Public API |

## 6. Verification

Tests: see LLRD `tests:` field and phase runner `test/libraries/run_phase8_tests.py`.
SVCP target: `test/libraries/VRP_Frsky_Telem/`
