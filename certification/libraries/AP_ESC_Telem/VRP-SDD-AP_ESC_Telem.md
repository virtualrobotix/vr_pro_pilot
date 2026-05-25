# VRP-SDD-AP_ESC_Telem — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_ESC_Telem` |
| LLRD | [`VRP-LLRD-AP_ESC_Telem.yaml`](VRP-LLRD-AP_ESC_Telem.yaml) |
| DAL | E |
| Status | partial |
| Phase | 12 |

## 1. Purpose

Clean-room BSD design for `VRP_ESC_Telem`, functional parity with ArduPilot `AP_ESC_Telem`.

## 2. Architecture

Baseline implementation present; integrated via `LibraryCore::tick()`. Roadmap phase **12** per `docs/CERTIFICATION_ROADMAP.md`.

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
| `VRP_ESC_Telem::init()` | Public API |
| `VRP_ESC_Telem::update(float throttle, float battery_v, uint64_t time_ms)` | Public API |
| `VRP_ESC_Telem::format_esc_telem(const EscTelemSample &s)` | Public API |

## 6. Verification

Tests: see LLRD `tests:` field and phase runner `test/libraries/run_phase12_tests.py`.
SVCP target: `test/libraries/VRP_ESC_Telem/`
