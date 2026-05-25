# VRP-SDD-AP_CANManager — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_CANManager` |
| LLRD | [`VRP-LLRD-AP_CANManager.yaml`](VRP-LLRD-AP_CANManager.yaml) |
| DAL | C |
| Status | partial |
| Phase | 2 |

## 1. Purpose

Clean-room BSD design for `VRP_CANManager`, functional parity with ArduPilot `AP_CANManager`.

## 2. Architecture

Baseline implementation present; integrated via `LibraryCore::tick()`. Roadmap phase **2** per `docs/CERTIFICATION_ROADMAP.md`.

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
| `VRP_CANManager::init()` | Public API |
| `VRP_CANManager::send_frame(uint32_t can_id, const uint8_t *data, uint8_t dlc)` | Public API |

## 6. Verification

Tests: see LLRD `tests:` field and phase runner `test/libraries/run_phase2_tests.py`.
SVCP target: `test/libraries/VRP_CANManager/`
