# VRP-SDD-AP_IOMCU — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_IOMCU` |
| LLRD | [`VRP-LLRD-AP_IOMCU.yaml`](VRP-LLRD-AP_IOMCU.yaml) |
| DAL | C |
| Status | partial |
| Phase | 19 |

## 1. Purpose

Clean-room BSD design for `VRP_IOMCU`, functional parity with ArduPilot `AP_IOMCU`.

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
| `VRP_IOMCU::init()` | Public API |
| `VRP_IOMCU::status(bool armed, uint64_t tick)` | Public API |
| `VRP_IOMCU::format_iomcu(const IomcuState &s)` | Public API |

## 6. Verification

Tests: see LLRD `tests:` field and phase runner `test/libraries/run_phase19_tests.py`.
SVCP target: `test/libraries/VRP_IOMCU/`
