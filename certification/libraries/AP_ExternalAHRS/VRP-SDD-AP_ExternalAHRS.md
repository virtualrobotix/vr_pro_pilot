# VRP-SDD-AP_ExternalAHRS — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_ExternalAHRS` |
| LLRD | [`VRP-LLRD-AP_ExternalAHRS.yaml`](VRP-LLRD-AP_ExternalAHRS.yaml) |
| DAL | B |
| Status | partial |
| Phase | 18 |

## 1. Purpose

Clean-room BSD design for `VRP_ExternalAHRS`, functional parity with ArduPilot `AP_ExternalAHRS`.

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
| `VRP_ExternalAHRS::init()` | Public API |
| `VRP_ExternalAHRS::update(const Attitude &att, bool armed)` | Public API |
| `VRP_ExternalAHRS::format_external_ahrs(const ExternalAhrsState &s)` | Public API |

## 6. Verification

Tests: see LLRD `tests:` field and phase runner `test/libraries/run_phase18_tests.py`.
SVCP target: `test/libraries/VRP_ExternalAHRS/`
