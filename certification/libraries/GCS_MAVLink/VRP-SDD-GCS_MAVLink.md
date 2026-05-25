# VRP-SDD-GCS_MAVLink — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_GCS_MAVLink` |
| LLRD | [`VRP-LLRD-GCS_MAVLink.yaml`](VRP-LLRD-GCS_MAVLink.yaml) |
| DAL | C |
| Status | partial |
| Phase | 6 |

## 1. Purpose

Clean-room BSD design for `VRP_GCS_MAVLink`, functional parity with ArduPilot `GCS_MAVLink`.

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
| `VRP_GCS_MAVLink::init()` | Public API |
| `VRP_GCS_MAVLink::shutdown()` | Public API |
| `VRP_GCS_MAVLink::transmit(const std::string &vehicle, bool armed, const std::string &mode, const Attitude &attitude,
                       const LocalPosition &pos, const GpsSample &gps, const BatteryStatus &battery, uint64_t time_ms,
                       uint16_t mission_seq = 0xFFFF, const MavlinkTxBundle *tx = nullptr,
                       const WindSample *wind = nullptr)` | Public API |
| `VRP_GCS_MAVLink::poll(MavlinkRxAction &action)` | Public API |
| `VRP_GCS_MAVLink::inject_frame_for_test(const std::vector<uint8_t> &frame, MavlinkRxAction &action)` | Public API |
| `VRP_GCS_MAVLink::dispatch_message(const MavlinkMessage &msg, MavlinkRxAction &action)` | Public API |

## 6. Verification

Tests: see LLRD `tests:` field and phase runner `test/libraries/run_phase6_tests.py`.
SVCP target: `test/libraries/VRP_GCS_MAVLink/`
