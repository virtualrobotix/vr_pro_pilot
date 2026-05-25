# VRP-SDD-doc — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_DOC` |
| LLRD | [`VRP-LLRD-doc.yaml`](VRP-LLRD-doc.yaml) |
| DAL | N/A |
| Status | n/a |
| Phase | 99 |

## 1. Purpose

Clean-room BSD design for `VRP_DOC`, functional parity with ArduPilot `doc`.

## 2. Architecture

Scaffold for future phase. Roadmap phase **99** per `docs/CERTIFICATION_ROADMAP.md`.

## 3. Data flow

Integrated through `LibraryCore` uORB `aux/*` telemetry unless promoted to vehicle core.
HAL boundary: `src/hal/` for board-specific I/O.

## 4. Safety constraints (DAL N/A)

- Documentation review only

Documentation-only; no airborne software artifact.

## 5. Interface summary

| API | Description |
|---|---|
| `VRP_DOC::init()` | Module initialization |
| `VRP_DOC::update()` | Periodic update |

## 6. Verification

Tests: see LLRD `tests:` field and phase runner `test/libraries/run_phase99_tests.py`.
SVCP target: `test/libraries/VRP_DOC/`
