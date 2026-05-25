# VRP-SDD-AP_LTM_Telem — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_LTM_Telem` |
| LLRD | [`VRP-LLRD-AP_LTM_Telem.yaml`](VRP-LLRD-AP_LTM_Telem.yaml) |
| DAL | E |
| Status | partial |
| Phase | 11 |

## 1. Purpose

Clean-room BSD design for `VRP_LTM_Telem`, functional parity with ArduPilot `AP_LTM_Telem`.

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
| `VRP_LTM_Telem::init()` | Public API |
| `VRP_LTM_Telem::update(const LocalPosition &pos, const GpsSample &gps, uint64_t time_ms)` | Public API |

## 6. Verification

Tests: see LLRD `tests:` field and phase runner `test/libraries/run_phase11_tests.py`.
SVCP target: `test/libraries/VRP_LTM_Telem/`
