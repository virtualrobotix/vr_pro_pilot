# VRP-SDD-AP_VideoTX — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_VideoTX` |
| LLRD | [`VRP-LLRD-AP_VideoTX.yaml`](VRP-LLRD-AP_VideoTX.yaml) |
| DAL | E |
| Status | partial |
| Phase | 14 |

## 1. Purpose

Clean-room BSD design for `VRP_VideoTX`, functional parity with ArduPilot `AP_VideoTX`.

## 2. Architecture

Baseline implementation present; integrated via `LibraryCore::tick()`. Roadmap phase **14** per `docs/CERTIFICATION_ROADMAP.md`.

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
| `VRP_VideoTX::init()` | Public API |
| `VRP_VideoTX::update(bool armed, uint64_t tick)` | Public API |
| `VRP_VideoTX::format_vtx(const VideoTxState &s)` | Public API |

## 6. Verification

Tests: see LLRD `tests:` field and phase runner `test/libraries/run_phase14_tests.py`.
SVCP target: `test/libraries/VRP_VideoTX/`
