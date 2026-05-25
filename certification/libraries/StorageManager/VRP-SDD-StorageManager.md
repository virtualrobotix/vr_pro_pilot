# VRP-SDD-StorageManager — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_StorageManager` |
| LLRD | [`VRP-LLRD-StorageManager.yaml`](VRP-LLRD-StorageManager.yaml) |
| DAL | C |
| Status | partial |
| Phase | 16 |

## 1. Purpose

Clean-room BSD design for `VRP_StorageManager`, functional parity with ArduPilot `StorageManager`.

## 2. Architecture

Baseline implementation present; integrated via `LibraryCore::tick()`. Roadmap phase **16** per `docs/CERTIFICATION_ROADMAP.md`.

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
| `VRP_StorageManager::init()` | Public API |
| `VRP_StorageManager::status(uint64_t tick)` | Public API |
| `VRP_StorageManager::format_storage_manager(const StorageManagerState &s)` | Public API |

## 6. Verification

Tests: see LLRD `tests:` field and phase runner `test/libraries/run_phase16_tests.py`.
SVCP target: `test/libraries/VRP_StorageManager/`
