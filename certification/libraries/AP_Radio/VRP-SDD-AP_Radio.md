# VRP-SDD-AP_Radio — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_Radio` |
| LLRD | [`VRP-LLRD-AP_Radio.yaml`](VRP-LLRD-AP_Radio.yaml) |
| DAL | C |
| Status | partial |
| Phase | 16 |

## 1. Purpose

Clean-room BSD design for `VRP_Radio`, functional parity with ArduPilot `AP_Radio`.

## 2. Architecture

Baseline implementation present; integrated via `LibraryCore::tick()`. Roadmap phase **16** per `docs/CERTIFICATION_ROADMAP.md`.

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
| `VRP_Radio::init()` | Public API |
| `VRP_Radio::update(const RssiSample &rssi, bool armed)` | Public API |
| `VRP_Radio::format_radio(const RadioState &s)` | Public API |

## 6. Verification

Tests: see LLRD `tests:` field and phase runner `test/libraries/run_phase16_tests.py`.
SVCP target: `test/libraries/VRP_Radio/`
