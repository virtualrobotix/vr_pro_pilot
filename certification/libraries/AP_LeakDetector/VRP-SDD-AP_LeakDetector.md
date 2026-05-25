# VRP-SDD-AP_LeakDetector — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_LeakDetector` |
| LLRD | [`VRP-LLRD-AP_LeakDetector.yaml`](VRP-LLRD-AP_LeakDetector.yaml) |
| DAL | C |
| Status | partial |
| Phase | 15 |

## 1. Purpose

Clean-room BSD design for `VRP_LeakDetector`, functional parity with ArduPilot `AP_LeakDetector`.

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
| `VRP_LeakDetector::init()` | Public API |
| `VRP_LeakDetector::update(bool armed, double depth_m, uint64_t tick)` | Public API |
| `VRP_LeakDetector::format_leak_detector(const LeakDetectorState &s)` | Public API |

## 6. Verification

Tests: see LLRD `tests:` field and phase runner `test/libraries/run_phase15_tests.py`.
SVCP target: `test/libraries/VRP_LeakDetector/`
