# VRP-SDD-AP_RCProtocol — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_RCProtocol` |
| LLRD | [`VRP-LLRD-AP_RCProtocol.yaml`](VRP-LLRD-AP_RCProtocol.yaml) |
| DAL | C |
| Status | partial |
| Phase | 3 |

## 1. Purpose

Clean-room BSD design for `VRP_RCProtocol`, functional parity with ArduPilot `AP_RCProtocol`.

## 2. Architecture

Baseline implementation present; integrated via `LibraryCore::tick()`. Roadmap phase **3** per `docs/CERTIFICATION_ROADMAP.md`.

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
| `VRP_RCProtocol::init()` | Public API |
| `VRP_RCProtocol::update(uint64_t tick)` | Public API |

## 6. Verification

Tests: see LLRD `tests:` field and phase runner `test/libraries/run_phase3_tests.py`.
SVCP target: `test/libraries/VRP_RCProtocol/`
