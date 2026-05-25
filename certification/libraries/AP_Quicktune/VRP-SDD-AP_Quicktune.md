# VRP-SDD-AP_Quicktune — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_Quicktune` |
| LLRD | [`VRP-LLRD-AP_Quicktune.yaml`](VRP-LLRD-AP_Quicktune.yaml) |
| DAL | D |
| Status | partial |
| Phase | 15 |

## 1. Purpose

Clean-room BSD design for `VRP_Quicktune`, functional parity with ArduPilot `AP_Quicktune`.

## 2. Architecture

Baseline implementation present; integrated via `LibraryCore::tick()`. Roadmap phase **15** per `docs/CERTIFICATION_ROADMAP.md`.

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
| `VRP_Quicktune::init()` | Public API |
| `VRP_Quicktune::update(bool armed, float aux1, uint64_t tick)` | Public API |
| `VRP_Quicktune::format_quicktune(const QuicktuneState &s)` | Public API |

## 6. Verification

Tests: see LLRD `tests:` field and phase runner `test/libraries/run_phase15_tests.py`.
SVCP target: `test/libraries/VRP_Quicktune/`
