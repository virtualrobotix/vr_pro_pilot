# VRP-SDD-AP_AIS — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_AIS` |
| LLRD | [`VRP-LLRD-AP_AIS.yaml`](VRP-LLRD-AP_AIS.yaml) |
| DAL | C |
| Status | partial |
| Phase | 12 |

## 1. Purpose

Clean-room BSD design for `VRP_AIS`, functional parity with ArduPilot `AP_AIS`.

## 2. Architecture

Baseline implementation present; integrated via `LibraryCore::tick()`. Roadmap phase **12** per `docs/CERTIFICATION_ROADMAP.md`.

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
| `VRP_AIS::init()` | Public API |
| `VRP_AIS::update(uint64_t tick, double own_x_m, double own_y_m)` | Public API |
| `VRP_AIS::format_ais(const AisVessel &v)` | Public API |

## 6. Verification

Tests: see LLRD `tests:` field and phase runner `test/libraries/run_phase12_tests.py`.
SVCP target: `test/libraries/VRP_AIS/`
