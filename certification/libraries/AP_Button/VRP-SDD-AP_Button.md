# VRP-SDD-AP_Button — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_Button` |
| LLRD | [`VRP-LLRD-AP_Button.yaml`](VRP-LLRD-AP_Button.yaml) |
| DAL | D |
| Status | partial |
| Phase | 20 |

## 1. Purpose

Clean-room BSD design for `VRP_Button`, functional parity with ArduPilot `AP_Button`.

## 2. Architecture

Baseline implementation present; integrated via `LibraryCore::tick()`. Roadmap phase **20** per `docs/CERTIFICATION_ROADMAP.md`.

## 3. Data flow

Integrated through `LibraryCore` uORB `aux/*` telemetry unless promoted to vehicle core.
HAL boundary: `src/hal/` for board-specific I/O.

## 4. Safety constraints (DAL D)

- Unit tests for public API
- Requirements traceability

Minor failure — requirements + unit tests.

## 5. Interface summary

| API | Description |
|---|---|
| `VRP_Button::init()` | Public API |
| `VRP_Button::update(bool armed, float aux1)` | Public API |
| `VRP_Button::format_button(const ButtonState &s)` | Public API |

## 6. Verification

Tests: see LLRD `tests:` field and phase runner `test/libraries/run_phase20_tests.py`.
SVCP target: `test/libraries/VRP_Button/`
