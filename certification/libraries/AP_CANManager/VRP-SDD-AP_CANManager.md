# VRP-SDD-AP_CANManager — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_CANManager` |
| LLRD | [`VRP-LLRD-AP_CANManager.yaml`](VRP-LLRD-AP_CANManager.yaml) |
| DAL | C |
| Status | planned |

## 1. Purpose

Clean-room BSD design for `VRP_CANManager`, functional parity with ArduPilot `AP_CANManager`.

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
| `VRP_CANManager::init()` | Module initialization |
| `VRP_CANManager::update()` | Periodic update |

## 6. Verification

See SVCP under `test/libraries/VRP_CANManager/` and LLRD test list.
