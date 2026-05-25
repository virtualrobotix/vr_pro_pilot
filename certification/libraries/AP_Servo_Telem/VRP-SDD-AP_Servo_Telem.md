# VRP-SDD-AP_Servo_Telem — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_Servo_Telem` |
| LLRD | [`VRP-LLRD-AP_Servo_Telem.yaml`](VRP-LLRD-AP_Servo_Telem.yaml) |
| DAL | E |
| Status | partial |
| Phase | 13 |

## 1. Purpose

Clean-room BSD design for `VRP_Servo_Telem`, functional parity with ArduPilot `AP_Servo_Telem`.

## 2. Architecture

Baseline implementation present; integrated via `LibraryCore::tick()`. Roadmap phase **13** per `docs/CERTIFICATION_ROADMAP.md`.

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
| `VRP_Servo_Telem::init()` | Public API |
| `VRP_Servo_Telem::update(float servo_cmd, float bus_v, uint64_t time_ms)` | Public API |
| `VRP_Servo_Telem::format_servo_telem(const ServoTelemSample &s)` | Public API |

## 6. Verification

Tests: see LLRD `tests:` field and phase runner `test/libraries/run_phase13_tests.py`.
SVCP target: `test/libraries/VRP_Servo_Telem/`
