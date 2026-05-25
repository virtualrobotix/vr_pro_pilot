# VRP-SDD-AP_MultiHeap — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_MultiHeap` |
| LLRD | [`VRP-LLRD-AP_MultiHeap.yaml`](VRP-LLRD-AP_MultiHeap.yaml) |
| DAL | C |
| Status | partial |
| Phase | 20 |

## 1. Purpose

Clean-room BSD design for `VRP_MultiHeap`, functional parity with ArduPilot `AP_MultiHeap`.

## 2. Architecture

Baseline implementation present; integrated via `LibraryCore::tick()`. Roadmap phase **20** per `docs/CERTIFICATION_ROADMAP.md`.

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
| `VRP_MultiHeap::init()` | Public API |
| `VRP_MultiHeap::format_multi_heap(const MultiHeapState &s)` | Public API |

## 6. Verification

Tests: see LLRD `tests:` field and phase runner `test/libraries/run_phase20_tests.py`.
SVCP target: `test/libraries/VRP_MultiHeap/`
