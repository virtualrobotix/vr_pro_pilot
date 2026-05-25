# VRP-SDD-AP_Param — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_Param` |
| LLRD | [`VRP-LLRD-AP_Param.yaml`](VRP-LLRD-AP_Param.yaml) |
| DAL | B |
| Status | partial |
| Phase | 0 |

## 1. Purpose

Clean-room BSD design for `VRP_Param`, functional parity with ArduPilot `AP_Param`.

## 2. Architecture

Baseline implementation present; integrated via `LibraryCore::tick()`. Roadmap phase **0** per `docs/CERTIFICATION_ROADMAP.md`.

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
| `VRP_Param::seed_defaults()` | Public API |
| `VRP_Param::set(const std::string &key, double value)` | Public API |
| `VRP_Param::set_by_name(const std::string &name, double value)` | Public API |

## 6. Verification

Tests: see LLRD `tests:` field and phase runner `test/libraries/run_phase0_tests.py`.
SVCP target: `test/libraries/VRP_Param/`
