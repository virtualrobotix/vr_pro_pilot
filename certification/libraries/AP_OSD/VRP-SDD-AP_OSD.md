# VRP-SDD-AP_OSD — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_OSD` |
| LLRD | [`VRP-LLRD-AP_OSD.yaml`](VRP-LLRD-AP_OSD.yaml) |
| DAL | C |
| Status | partial |
| Phase | 3 |

## 1. Purpose

Clean-room BSD design for `VRP_OSD`, functional parity with ArduPilot `AP_OSD`.

## 2. Architecture

Baseline implementation present; integrated via `LibraryCore::tick()`. Roadmap phase **3** per `docs/CERTIFICATION_ROADMAP.md`.

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
| `VRP_OSD::init()` | Public API |

## 6. Verification

Tests: see LLRD `tests:` field and phase runner `test/libraries/run_phase3_tests.py`.
SVCP target: `test/libraries/VRP_OSD/`
