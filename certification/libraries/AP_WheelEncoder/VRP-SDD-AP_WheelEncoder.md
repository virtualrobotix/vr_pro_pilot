# VRP-SDD-AP_WheelEncoder — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_WheelEncoder` |
| LLRD | [`VRP-LLRD-AP_WheelEncoder.yaml`](VRP-LLRD-AP_WheelEncoder.yaml) |
| DAL | C |
| Status | partial |
| Phase | 15 |

## 1. Purpose

Clean-room BSD design for `VRP_WheelEncoder`, functional parity with ArduPilot `AP_WheelEncoder`.

## 2. Architecture

Baseline implementation present; integrated via `LibraryCore::tick()`. Roadmap phase **15** per `docs/CERTIFICATION_ROADMAP.md`.

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
| `VRP_WheelEncoder::init()` | Public API |
| `VRP_WheelEncoder::update(double dx_m, double dy_m, bool armed)` | Public API |
| `VRP_WheelEncoder::format_wheel_encoder(const WheelEncoderState &s)` | Public API |

## 6. Verification

Tests: see LLRD `tests:` field and phase runner `test/libraries/run_phase15_tests.py`.
SVCP target: `test/libraries/VRP_WheelEncoder/`
