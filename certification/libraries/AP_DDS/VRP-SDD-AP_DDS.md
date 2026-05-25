# VRP-SDD-AP_DDS — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_DDS` |
| LLRD | [`VRP-LLRD-AP_DDS.yaml`](VRP-LLRD-AP_DDS.yaml) |
| DAL | C |
| Status | partial |
| Phase | 10 |

## 1. Purpose

Clean-room BSD design for `VRP_DDS`, functional parity with ArduPilot `AP_DDS`.

## 2. Architecture

Baseline implementation present; integrated via `LibraryCore::tick()`. Roadmap phase **10** per `docs/CERTIFICATION_ROADMAP.md`.

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
| `VRP_DDS::init()` | Public API |
| `VRP_DDS::publish_status(const std::string &mode, bool armed, UORB &uorb)` | Public API |
| `VRP_DDS::publish_attitude(UORB &uorb)` | Public API |
| `VRP_DDS::publish_position(UORB &uorb)` | Public API |
| `VRP_DDS::publish_sensor_combined(UORB &uorb)` | Public API |
| `VRP_DDS::poll_subscriptions(UORB &uorb)` | Public API |
| `VRP_DDS::tick(uint64_t time_ms, const std::string &mode, bool armed, UORB &uorb)` | Public API |

## 6. Verification

Tests: see LLRD `tests:` field and phase runner `test/libraries/run_phase10_tests.py`.
SVCP target: `test/libraries/VRP_DDS/`
