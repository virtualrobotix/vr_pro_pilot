# VRP-SDD-AP_Soaring — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_Soaring` |
| LLRD | [`VRP-LLRD-AP_Soaring.yaml`](VRP-LLRD-AP_Soaring.yaml) |
| DAL | C |
| Status | partial |
| Phase | 12 |

## 1. Purpose

Clean-room BSD design for `VRP_Soaring`, functional parity with ArduPilot `AP_Soaring`.

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
| `VRP_Soaring::init()` | Public API |
| `VRP_Soaring::update(double alt_m, double climb_m_s)` | Public API |
| `VRP_Soaring::format_soaring(const SoaringState &s)` | Public API |

## 6. Verification

Tests: see LLRD `tests:` field and phase runner `test/libraries/run_phase12_tests.py`.
SVCP target: `test/libraries/VRP_Soaring/`
