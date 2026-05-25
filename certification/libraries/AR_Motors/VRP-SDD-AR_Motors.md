# VRP-SDD-AR_Motors — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_AR_Motors` |
| LLRD | [`VRP-LLRD-AR_Motors.yaml`](VRP-LLRD-AR_Motors.yaml) |
| DAL | B |
| Status | partial |
| Phase | 18 |

## 1. Purpose

Clean-room BSD design for `VRP_AR_Motors`, functional parity with ArduPilot `AR_Motors`.

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
| `VRP_AR_Motors::init(ArFrameClass frame = ArFrameClass::Boat, bool skid_steering = true)` | Public API |
| `VRP_AR_Motors::update(float throttle, float steering, bool armed)` | Public API |
| `VRP_AR_Motors::format_ar_motors(const ArMotorsState &s)` | Public API |

## 6. Verification

Tests: see LLRD `tests:` field and phase runner `test/libraries/run_phase18_tests.py`.
SVCP target: `test/libraries/VRP_AR_Motors/`
