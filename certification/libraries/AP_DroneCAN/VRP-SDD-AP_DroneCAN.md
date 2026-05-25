# VRP-SDD-AP_DroneCAN — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_DroneCAN` |
| LLRD | [`VRP-LLRD-AP_DroneCAN.yaml`](VRP-LLRD-AP_DroneCAN.yaml) |
| DAL | C |
| Status | partial |
| Phase | 6 |

## 1. Purpose

Clean-room BSD design for `VRP_DroneCAN`, functional parity with ArduPilot `AP_DroneCAN`.

## 2. Architecture

Baseline implementation present; integrated via `LibraryCore::tick()`. Roadmap phase **6** per `docs/CERTIFICATION_ROADMAP.md`.

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
| `VRP_DroneCAN::init(uint8_t node_id)` | Public API |
| `VRP_DroneCAN::heartbeat(uint64_t time_ms)` | Public API |
| `VRP_DroneCAN::esc_status(uint64_t time_ms, float throttle)` | Public API |
| `VRP_DroneCAN::publish_esc(VRP_CANManager &can, float throttle)` | Public API |

## 6. Verification

Tests: see LLRD `tests:` field and phase runner `test/libraries/run_phase6_tests.py`.
SVCP target: `test/libraries/VRP_DroneCAN/`
