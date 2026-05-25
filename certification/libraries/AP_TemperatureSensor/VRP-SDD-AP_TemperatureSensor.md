# VRP-SDD-AP_TemperatureSensor — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_TemperatureSensor` |
| LLRD | [`VRP-LLRD-AP_TemperatureSensor.yaml`](VRP-LLRD-AP_TemperatureSensor.yaml) |
| DAL | C |
| Status | partial |
| Phase | 14 |

## 1. Purpose

Clean-room BSD design for `VRP_TemperatureSensor`, functional parity with ArduPilot `AP_TemperatureSensor`.

## 2. Architecture

Baseline implementation present; integrated via `LibraryCore::tick()`. Roadmap phase **14** per `docs/CERTIFICATION_ROADMAP.md`.

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
| `VRP_TemperatureSensor::init()` | Public API |
| `VRP_TemperatureSensor::update(float throttle, uint64_t tick)` | Public API |
| `VRP_TemperatureSensor::format_temperature(const TemperatureSample &s)` | Public API |

## 6. Verification

Tests: see LLRD `tests:` field and phase runner `test/libraries/run_phase14_tests.py`.
SVCP target: `test/libraries/VRP_TemperatureSensor/`
