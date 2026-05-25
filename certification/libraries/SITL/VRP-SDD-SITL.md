# VRP-SDD-SITL — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_SITL` |
| LLRD | [`VRP-LLRD-SITL.yaml`](VRP-LLRD-SITL.yaml) |
| DAL | C |
| Status | partial |
| Phase | 0 |

## 1. Purpose

Clean-room BSD design for `VRP_SITL`, functional parity with ArduPilot `SITL`.

## 2. Architecture

Baseline implementation present; integrated via `LibraryCore::tick()`. Roadmap phase **0** per `docs/CERTIFICATION_ROADMAP.md`.

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
| `VRP_SITL::init()` | Module initialization |
| `VRP_SITL::update()` | Periodic update |

## 6. Verification

Tests: see LLRD `tests:` field and phase runner `test/libraries/run_phase0_tests.py`.
SVCP target: `test/libraries/VRP_SITL/`
