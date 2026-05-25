# VRP-SDD-AP_NMEA_Output — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_NMEA_Output` |
| LLRD | [`VRP-LLRD-AP_NMEA_Output.yaml`](VRP-LLRD-AP_NMEA_Output.yaml) |
| DAL | C |
| Status | partial |
| Phase | 15 |

## 1. Purpose

Clean-room BSD design for `VRP_NMEA_Output`, functional parity with ArduPilot `AP_NMEA_Output`.

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
| `VRP_NMEA_Output::init()` | Public API |
| `VRP_NMEA_Output::update(const GpsSample &gps, bool armed, uint64_t tick)` | Public API |
| `VRP_NMEA_Output::format_nmea_output(const NmeaOutputState &s)` | Public API |

## 6. Verification

Tests: see LLRD `tests:` field and phase runner `test/libraries/run_phase15_tests.py`.
SVCP target: `test/libraries/VRP_NMEA_Output/`
