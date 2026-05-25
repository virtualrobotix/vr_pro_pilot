# VRP-SDD-AP_GyroFFT — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_GyroFFT` |
| LLRD | [`VRP-LLRD-AP_GyroFFT.yaml`](VRP-LLRD-AP_GyroFFT.yaml) |
| DAL | C |
| Status | partial |
| Phase | 19 |

## 1. Purpose

Clean-room BSD design for `VRP_GyroFFT`, functional parity with ArduPilot `AP_GyroFFT`.

## 2. Architecture

Baseline implementation present; integrated via `LibraryCore::tick()`. Roadmap phase **19** per `docs/CERTIFICATION_ROADMAP.md`.

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
| `VRP_GyroFFT::init()` | Public API |
| `VRP_GyroFFT::update(bool armed, float gyro_z, uint64_t tick)` | Public API |
| `VRP_GyroFFT::format_gyro_fft(const GyroFftState &s)` | Public API |

## 6. Verification

Tests: see LLRD `tests:` field and phase runner `test/libraries/run_phase19_tests.py`.
SVCP target: `test/libraries/VRP_GyroFFT/`
