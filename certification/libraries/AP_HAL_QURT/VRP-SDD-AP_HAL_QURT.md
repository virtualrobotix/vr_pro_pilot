# VRP-SDD-AP_HAL_QURT — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_HAL_QURT` |
| LLRD | [`VRP-LLRD-AP_HAL_QURT.yaml`](VRP-LLRD-AP_HAL_QURT.yaml) |
| DAL | E |
| Status | partial |
| Phase | 20 |

## 1. Purpose

Clean-room BSD design for `VRP_HAL_QURT`, functional parity with ArduPilot `AP_HAL_QURT`.

## 2. Architecture

Baseline implementation present; integrated via `LibraryCore::tick()`. Roadmap phase **20** per `docs/CERTIFICATION_ROADMAP.md`.

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
| `VRP_HAL_QURT::init()` | Public API |
| `VRP_HAL_QURT::format_hal_qurt(const HalQurtState &s)` | Public API |

## 6. Verification

Tests: see LLRD `tests:` field and phase runner `test/libraries/run_phase20_tests.py`.
SVCP target: `test/libraries/VRP_HAL_QURT/`
