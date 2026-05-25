# VRP-SDD-AP_Proximity — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_Proximity` |
| LLRD | [`VRP-LLRD-AP_Proximity.yaml`](VRP-LLRD-AP_Proximity.yaml) |
| DAL | C |
| Status | planned |

## 1. Purpose

Clean-room BSD design for `VRP_Proximity`, functional parity with ArduPilot `AP_Proximity`.

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
| `VRP_Proximity::init()` | Module initialization |
| `VRP_Proximity::update()` | Periodic update |

## 6. Verification

See SVCP under `test/libraries/VRP_Proximity/` and LLRD test list.
