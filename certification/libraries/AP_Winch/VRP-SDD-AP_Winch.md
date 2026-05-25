# VRP-SDD-AP_Winch — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_Winch` |
| LLRD | [`VRP-LLRD-AP_Winch.yaml`](VRP-LLRD-AP_Winch.yaml) |
| DAL | C |
| Status | partial |
| Phase | 13 |

## 1. Purpose

Clean-room BSD design for `VRP_Winch`, functional parity with ArduPilot `AP_Winch`.

## 2. Architecture

Baseline implementation present; integrated via `LibraryCore::tick()`. Roadmap phase **13** per `docs/CERTIFICATION_ROADMAP.md`.

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
| `VRP_Winch::init()` | Public API |
| `VRP_Winch::update(float command, bool armed)` | Public API |
| `VRP_Winch::format_winch(const WinchState &s)` | Public API |

## 6. Verification

Tests: see LLRD `tests:` field and phase runner `test/libraries/run_phase13_tests.py`.
SVCP target: `test/libraries/VRP_Winch/`
