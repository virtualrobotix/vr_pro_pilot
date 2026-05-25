# VRP-SDD-AP_Navigation — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_Navigation` |
| LLRD | [`VRP-LLRD-AP_Navigation.yaml`](VRP-LLRD-AP_Navigation.yaml) |
| DAL | C |
| Status | partial |
| Phase | 18 |

## 1. Purpose

Clean-room BSD design for `VRP_Navigation`, functional parity with ArduPilot `AP_Navigation`.

## 2. Architecture

Baseline implementation present; integrated via `LibraryCore::tick()`. Roadmap phase **18** per `docs/CERTIFICATION_ROADMAP.md`.

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
| `VRP_Navigation::init()` | Public API |
| `VRP_Navigation::update(const std::string &mode, const LocalPosition &pos, double target_x, double target_y)` | Public API |
| `VRP_Navigation::format_navigation(const NavigationState &s)` | Public API |

## 6. Verification

Tests: see LLRD `tests:` field and phase runner `test/libraries/run_phase18_tests.py`.
SVCP target: `test/libraries/VRP_Navigation/`
