# VRP-SDD-AP_PiccoloCAN — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_PiccoloCAN` |
| LLRD | [`VRP-LLRD-AP_PiccoloCAN.yaml`](VRP-LLRD-AP_PiccoloCAN.yaml) |
| DAL | C |
| Status | partial |
| Phase | 15 |

## 1. Purpose

Clean-room BSD design for `VRP_PiccoloCAN`, functional parity with ArduPilot `AP_PiccoloCAN`.

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
| `VRP_PiccoloCAN::init()` | Public API |
| `VRP_PiccoloCAN::update(bool armed, uint64_t tick)` | Public API |
| `VRP_PiccoloCAN::format_piccolo_can(const PiccoloCanState &s)` | Public API |

## 6. Verification

Tests: see LLRD `tests:` field and phase runner `test/libraries/run_phase15_tests.py`.
SVCP target: `test/libraries/VRP_PiccoloCAN/`
