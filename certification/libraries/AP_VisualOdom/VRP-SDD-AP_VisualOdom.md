# VRP-SDD-AP_VisualOdom — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_VisualOdom` |
| LLRD | [`VRP-LLRD-AP_VisualOdom.yaml`](VRP-LLRD-AP_VisualOdom.yaml) |
| DAL | C |
| Status | partial |
| Phase | 14 |

## 1. Purpose

Clean-room BSD design for `VRP_VisualOdom`, functional parity with ArduPilot `AP_VisualOdom`.

## 2. Architecture

Baseline implementation present; integrated via `LibraryCore::tick()`. Roadmap phase **14** per `docs/CERTIFICATION_ROADMAP.md`.

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
| `VRP_VisualOdom::init()` | Public API |
| `VRP_VisualOdom::update(double dx_m, double dy_m, double dt_s)` | Public API |
| `VRP_VisualOdom::format_visual_odom(const VisualOdomState &s)` | Public API |

## 6. Verification

Tests: see LLRD `tests:` field and phase runner `test/libraries/run_phase14_tests.py`.
SVCP target: `test/libraries/VRP_VisualOdom/`
