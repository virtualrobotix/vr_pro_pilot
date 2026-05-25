# VRP-SDD-AP_ONVIF — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_ONVIF` |
| LLRD | [`VRP-LLRD-AP_ONVIF.yaml`](VRP-LLRD-AP_ONVIF.yaml) |
| DAL | E |
| Status | partial |
| Phase | 17 |

## 1. Purpose

Clean-room BSD design for `VRP_ONVIF`, functional parity with ArduPilot `AP_ONVIF`.

## 2. Architecture

Baseline implementation present; integrated via `LibraryCore::tick()`. Roadmap phase **17** per `docs/CERTIFICATION_ROADMAP.md`.

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
| `VRP_ONVIF::init()` | Public API |
| `VRP_ONVIF::update(bool armed, bool gcs_link, uint64_t tick)` | Public API |
| `VRP_ONVIF::format_onvif(const OnvifState &s)` | Public API |

## 6. Verification

Tests: see LLRD `tests:` field and phase runner `test/libraries/run_phase17_tests.py`.
SVCP target: `test/libraries/VRP_ONVIF/`
