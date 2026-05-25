# VRP-SDD-AP_RCTelemetry — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_RCTelemetry` |
| LLRD | [`VRP-LLRD-AP_RCTelemetry.yaml`](VRP-LLRD-AP_RCTelemetry.yaml) |
| DAL | E |
| Status | partial |
| Phase | 12 |

## 1. Purpose

Clean-room BSD design for `VRP_RCTelemetry`, functional parity with ArduPilot `AP_RCTelemetry`.

## 2. Architecture

Baseline implementation present; integrated via `LibraryCore::tick()`. Roadmap phase **12** per `docs/CERTIFICATION_ROADMAP.md`.

## 3. Data flow

Integrated through `LibraryCore` uORB `aux/*` telemetry unless promoted to vehicle core.
HAL boundary: `src/hal/` for board-specific I/O.

## 4. Safety constraints (DAL E)

- Smoke tests
- Best-effort review

No safety effect — best-effort tests.

## 5. Interface summary

| API | Description |
|---|---|
| `VRP_RCTelemetry::init()` | Public API |
| `VRP_RCTelemetry::update(const RcChannels &rc, const RssiSample &rssi, uint64_t time_ms)` | Public API |

## 6. Verification

Tests: see LLRD `tests:` field and phase runner `test/libraries/run_phase12_tests.py`.
SVCP target: `test/libraries/VRP_RCTelemetry/`
