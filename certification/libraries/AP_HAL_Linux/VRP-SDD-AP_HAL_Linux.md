# VRP-SDD-AP_HAL_Linux — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_HAL_Linux` |
| LLRD | [`VRP-LLRD-AP_HAL_Linux.yaml`](VRP-LLRD-AP_HAL_Linux.yaml) |
| DAL | E |
| Status | partial |
| Phase | 18 |

## 1. Purpose

Clean-room BSD design for `VRP_HAL_Linux`, functional parity with ArduPilot `AP_HAL_Linux`.

## 2. Architecture

Baseline implementation present; integrated via `LibraryCore::tick()`. Roadmap phase **18** per `docs/CERTIFICATION_ROADMAP.md`.

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
| `VRP_HAL_Linux::init()` | Public API |
| `VRP_HAL_Linux::format_hal_linux(const HalLinuxState &s)` | Public API |

## 6. Verification

Tests: see LLRD `tests:` field and phase runner `test/libraries/run_phase18_tests.py`.
SVCP target: `test/libraries/VRP_HAL_Linux/`
