# VRP-SDD-AP_BLHeli — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_BLHeli` |
| LLRD | [`VRP-LLRD-AP_BLHeli.yaml`](VRP-LLRD-AP_BLHeli.yaml) |
| DAL | C |
| Status | planned |

## 1. Purpose

Clean-room BSD design for `VRP_BLHeli`, functional parity with ArduPilot `AP_BLHeli`.

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
| `VRP_BLHeli::init()` | Module initialization |
| `VRP_BLHeli::update()` | Periodic update |

## 6. Verification

See SVCP under `test/libraries/VRP_BLHeli/` and LLRD test list.
