# VRP-SDD-AP_Generator — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_Generator` |
| LLRD | [`VRP-LLRD-AP_Generator.yaml`](VRP-LLRD-AP_Generator.yaml) |
| DAL | C |
| Status | partial |
| Phase | 14 |

## 1. Purpose

Clean-room BSD design for `VRP_Generator`, functional parity with ArduPilot `AP_Generator`.

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
| `VRP_Generator::init()` | Public API |
| `VRP_Generator::update(float throttle, bool armed)` | Public API |
| `VRP_Generator::format_generator(const GeneratorState &s)` | Public API |

## 6. Verification

Tests: see LLRD `tests:` field and phase runner `test/libraries/run_phase14_tests.py`.
SVCP target: `test/libraries/VRP_Generator/`
