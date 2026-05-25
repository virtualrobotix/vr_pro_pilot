# VRP-SDD-AC_Autorotation — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_AC_Autorotation` |
| LLRD | [`VRP-LLRD-AC_Autorotation.yaml`](VRP-LLRD-AC_Autorotation.yaml) |
| DAL | B |
| Status | partial |
| Phase | 18 |

## 1. Purpose

Clean-room BSD design for `VRP_AC_Autorotation`, functional parity with ArduPilot `AC_Autorotation`.

## 2. Architecture

Baseline implementation present; integrated via `LibraryCore::tick()`. Roadmap phase **18** per `docs/CERTIFICATION_ROADMAP.md`.

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
| `VRP_AC_Autorotation::init()` | Public API |
| `VRP_AC_Autorotation::update(bool armed, bool rtl_active, float throttle)` | Public API |
| `VRP_AC_Autorotation::format_autorotation(const AutorotationState &s)` | Public API |

## 6. Verification

Tests: see LLRD `tests:` field and phase runner `test/libraries/run_phase18_tests.py`.
SVCP target: `test/libraries/VRP_AC_Autorotation/`
