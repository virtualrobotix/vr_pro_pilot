# VRP-SDD-AC_InputManager — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_AC_InputManager` |
| LLRD | [`VRP-LLRD-AC_InputManager.yaml`](VRP-LLRD-AC_InputManager.yaml) |
| DAL | C |
| Status | planned |

## 1. Purpose

Clean-room BSD design for `VRP_AC_InputManager`, functional parity with ArduPilot `AC_InputManager`.

## 2. Architecture

_TBD during implementation phase 3._

## 3. Data flow

_TBD — uORB topics / HAL interfaces._

## 4. Safety constraints (DAL C)

- Statement coverage 100%
- Requirements-based tests
- Design review

## 5. Interface summary

| API | Description |
|---|---|
| `VRP_AC_InputManager::init()` | Module initialization |
| `VRP_AC_InputManager::update()` | Periodic update |

## 6. Verification

See SVCP under `test/libraries/VRP_AC_InputManager/` and LLRD test list.
