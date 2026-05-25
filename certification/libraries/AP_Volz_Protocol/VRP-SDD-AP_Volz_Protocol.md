# VRP-SDD-AP_Volz_Protocol — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_Volz_Protocol` |
| LLRD | [`VRP-LLRD-AP_Volz_Protocol.yaml`](VRP-LLRD-AP_Volz_Protocol.yaml) |
| DAL | C |
| Status | partial |
| Phase | 17 |

## 1. Purpose

Clean-room BSD design for `VRP_Volz_Protocol`, functional parity with ArduPilot `AP_Volz_Protocol`.

## 2. Architecture

Baseline implementation present; integrated via `LibraryCore::tick()`. Roadmap phase **17** per `docs/CERTIFICATION_ROADMAP.md`.

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
| `VRP_Volz_Protocol::init()` | Public API |
| `VRP_Volz_Protocol::update(float command, bool armed, uint64_t tick)` | Public API |
| `VRP_Volz_Protocol::format_volz(const VolzState &s)` | Public API |

## 6. Verification

Tests: see LLRD `tests:` field and phase runner `test/libraries/run_phase17_tests.py`.
SVCP target: `test/libraries/VRP_Volz_Protocol/`
