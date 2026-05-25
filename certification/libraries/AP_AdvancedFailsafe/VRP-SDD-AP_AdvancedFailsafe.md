# VRP-SDD-AP_AdvancedFailsafe — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_AdvancedFailsafe` |
| LLRD | [`VRP-LLRD-AP_AdvancedFailsafe.yaml`](VRP-LLRD-AP_AdvancedFailsafe.yaml) |
| DAL | B |
| Status | partial |
| Phase | 7 |

## 1. Purpose

Clean-room BSD design for `VRP_AdvancedFailsafe`, functional parity with ArduPilot `AP_AdvancedFailsafe`.

## 2. Architecture

Baseline implementation present; integrated via `LibraryCore::tick()`. Roadmap phase **7** per `docs/CERTIFICATION_ROADMAP.md`.

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
| `VRP_AdvancedFailsafe::init(VRPParamStore &params)` | Public API |
| `VRP_AdvancedFailsafe::note_gcs_link(uint64_t tick)` | Public API |
| `VRP_AdvancedFailsafe::update(uint64_t tick, const BatteryStatus &battery, bool armed)` | Public API |

## 6. Verification

Tests: see LLRD `tests:` field and phase runner `test/libraries/run_phase7_tests.py`.
SVCP target: `test/libraries/VRP_AdvancedFailsafe/`
