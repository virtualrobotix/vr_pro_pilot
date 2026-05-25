# VRP-SDD-AP_Relay — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_Relay` |
| LLRD | [`VRP-LLRD-AP_Relay.yaml`](VRP-LLRD-AP_Relay.yaml) |
| DAL | C |
| Status | partial |
| Phase | 13 |

## 1. Purpose

Clean-room BSD design for `VRP_Relay`, functional parity with ArduPilot `AP_Relay`.

## 2. Architecture

Baseline implementation present; integrated via `LibraryCore::tick()`. Roadmap phase **13** per `docs/CERTIFICATION_ROADMAP.md`.

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
| `VRP_Relay::init()` | Public API |
| `VRP_Relay::format_relay(const std::array<uint8_t, 4> &channels)` | Public API |

## 6. Verification

Tests: see LLRD `tests:` field and phase runner `test/libraries/run_phase13_tests.py`.
SVCP target: `test/libraries/VRP_Relay/`
