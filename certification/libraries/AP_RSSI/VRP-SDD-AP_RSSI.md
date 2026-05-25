# VRP-SDD-AP_RSSI — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_RSSI` |
| LLRD | [`VRP-LLRD-AP_RSSI.yaml`](VRP-LLRD-AP_RSSI.yaml) |
| DAL | E |
| Status | partial |
| Phase | 11 |

## 1. Purpose

Clean-room BSD design for `VRP_RSSI`, functional parity with ArduPilot `AP_RSSI`.

## 2. Architecture

Baseline implementation present; integrated via `LibraryCore::tick()`. Roadmap phase **11** per `docs/CERTIFICATION_ROADMAP.md`.

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
| `VRP_RSSI::init()` | Public API |
| `VRP_RSSI::update(uint64_t tick, bool gcs_link)` | Public API |
| `VRP_RSSI::format_rssi(const RssiSample &s)` | Public API |

## 6. Verification

Tests: see LLRD `tests:` field and phase runner `test/libraries/run_phase11_tests.py`.
SVCP target: `test/libraries/VRP_RSSI/`
