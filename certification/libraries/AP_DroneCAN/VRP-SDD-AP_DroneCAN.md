# VRP-SDD-AP_DroneCAN — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_DroneCAN` |
| LLRD | [`VRP-LLRD-AP_DroneCAN.yaml`](VRP-LLRD-AP_DroneCAN.yaml) |
| DAL | C |
| Status | planned |

## 1. Purpose

Clean-room BSD design for `VRP_DroneCAN`, functional parity with ArduPilot `AP_DroneCAN`.

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
| `VRP_DroneCAN::init()` | Module initialization |
| `VRP_DroneCAN::update()` | Periodic update |

## 6. Verification

See SVCP under `test/libraries/VRP_DroneCAN/` and LLRD test list.
