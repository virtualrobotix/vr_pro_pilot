# VRP-SDD-AP_InternalError — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_InternalError` |
| LLRD | [`VRP-LLRD-AP_InternalError.yaml`](VRP-LLRD-AP_InternalError.yaml) |
| DAL | B |
| Status | partial |
| Phase | 18 |

## 1. Purpose

Clean-room BSD design for `VRP_InternalError`, functional parity with ArduPilot `AP_InternalError`.

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
| `VRP_InternalError::init()` | Public API |
| `VRP_InternalError::update(bool armed, uint64_t tick)` | Public API |
| `VRP_InternalError::format_internal_error(const InternalErrorState &s)` | Public API |

## 6. Verification

Tests: see LLRD `tests:` field and phase runner `test/libraries/run_phase18_tests.py`.
SVCP target: `test/libraries/VRP_InternalError/`
