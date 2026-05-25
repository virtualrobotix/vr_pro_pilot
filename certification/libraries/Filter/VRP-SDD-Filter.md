# VRP-SDD-Filter — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_Filter` |
| LLRD | [`VRP-LLRD-Filter.yaml`](VRP-LLRD-Filter.yaml) |
| DAL | B |
| Status | partial |
| Phase | 1 |

## 1. Purpose

Clean-room BSD design for `VRP_Filter`, functional parity with ArduPilot `Filter`.

## 2. Architecture

Baseline implementation present; integrated via `LibraryCore::tick()`. Roadmap phase **1** per `docs/CERTIFICATION_ROADMAP.md`.

## 3. Data flow

Integrated through `LibraryCore` uORB `aux/*` telemetry unless promoted to vehicle core.
HAL boundary: `src/hal/` for board-specific I/O.

## 4. Safety constraints (DAL B)

- MC/DC on safety paths
- No dynamic heap
- Bounded WCET
- MISRA subset

Hazardous failure — MC/DC on safety paths, no heap, bounded WCET.

## 5. Interface summary

| API | Description |
|---|---|
| `VRP_Filter::init()` | Module initialization |
| `VRP_Filter::update()` | Periodic update |

## 6. Verification

Tests: see LLRD `tests:` field and phase runner `test/libraries/run_phase1_tests.py`.
SVCP target: `test/libraries/VRP_Filter/`
