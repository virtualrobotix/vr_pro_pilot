# VRP-SDD-AP_FlashIface — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_FlashIface` |
| LLRD | [`VRP-LLRD-AP_FlashIface.yaml`](VRP-LLRD-AP_FlashIface.yaml) |
| DAL | C |
| Status | partial |
| Phase | 10 |

## 1. Purpose

Clean-room BSD design for `VRP_FlashIface`, functional parity with ArduPilot `AP_FlashIface`.

## 2. Architecture

Baseline implementation present; integrated via `LibraryCore::tick()`. Roadmap phase **10** per `docs/CERTIFICATION_ROADMAP.md`.

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
| `VRP_FlashIface::init()` | Public API |
| `VRP_FlashIface::write(uint32_t offset, const uint8_t *buf, size_t len)` | Public API |
| `VRP_FlashIface::erase_sector(uint32_t sector)` | Public API |

## 6. Verification

Tests: see LLRD `tests:` field and phase runner `test/libraries/run_phase10_tests.py`.
SVCP target: `test/libraries/VRP_FlashIface/`
