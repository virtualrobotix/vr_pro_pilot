# VRP-SDD-AP_Scripting — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_Scripting` |
| LLRD | [`VRP-LLRD-AP_Scripting.yaml`](VRP-LLRD-AP_Scripting.yaml) |
| DAL | D |
| Status | partial |
| Phase | 3 |

## 1. Purpose

Clean-room BSD design for `VRP_Scripting`, functional parity with ArduPilot `AP_Scripting`.

## 2. Architecture

Baseline implementation present; integrated via `LibraryCore::tick()`. Roadmap phase **3** per `docs/CERTIFICATION_ROADMAP.md`.

## 3. Data flow

Integrated through `LibraryCore` uORB `aux/*` telemetry unless promoted to vehicle core.
HAL boundary: `src/hal/` for board-specific I/O.

## 4. Safety constraints (DAL D)

- Unit tests for public API
- Requirements traceability

Minor failure — requirements + unit tests.

## 5. Interface summary

| API | Description |
|---|---|
| `VRP_Scripting::init(bool enable)` | Public API |
| `VRP_Scripting::update(uint64_t tick, const std::string &current_mode)` | Public API |

## 6. Verification

Tests: see LLRD `tests:` field and phase runner `test/libraries/run_phase3_tests.py`.
SVCP target: `test/libraries/VRP_Scripting/`
