# VRP-SDD-AP_BLHeli — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_BLHeli` |
| LLRD | [`VRP-LLRD-AP_BLHeli.yaml`](VRP-LLRD-AP_BLHeli.yaml) |
| DAL | C |
| Status | partial |
| Phase | 15 |

## 1. Purpose

Clean-room BSD design for `VRP_BLHeli`, functional parity with ArduPilot `AP_BLHeli`.

## 2. Architecture

Baseline implementation present; integrated via `LibraryCore::tick()`. Roadmap phase **15** per `docs/CERTIFICATION_ROADMAP.md`.

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
| `VRP_BLHeli::init()` | Public API |
| `VRP_BLHeli::update(float throttle, bool armed)` | Public API |
| `VRP_BLHeli::format_blheli(const BLHeliState &s)` | Public API |

## 6. Verification

Tests: see LLRD `tests:` field and phase runner `test/libraries/run_phase15_tests.py`.
SVCP target: `test/libraries/VRP_BLHeli/`
