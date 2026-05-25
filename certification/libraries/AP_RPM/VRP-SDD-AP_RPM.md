# VRP-SDD-AP_RPM — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_RPM` |
| LLRD | [`VRP-LLRD-AP_RPM.yaml`](VRP-LLRD-AP_RPM.yaml) |
| DAL | E |
| Status | partial |
| Phase | 12 |

## 1. Purpose

Clean-room BSD design for `VRP_RPM`, functional parity with ArduPilot `AP_RPM`.

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
| `VRP_RPM::init()` | Public API |
| `VRP_RPM::update(float throttle)` | Public API |
| `VRP_RPM::format_rpm(const RpmSample &s)` | Public API |

## 6. Verification

Tests: see LLRD `tests:` field and phase runner `test/libraries/run_phase12_tests.py`.
SVCP target: `test/libraries/VRP_RPM/`
