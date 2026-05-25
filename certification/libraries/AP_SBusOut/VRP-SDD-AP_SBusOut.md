# VRP-SDD-AP_SBusOut — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_SBusOut` |
| LLRD | [`VRP-LLRD-AP_SBusOut.yaml`](VRP-LLRD-AP_SBusOut.yaml) |
| DAL | C |
| Status | planned |

## 1. Purpose

Clean-room BSD design for `VRP_SBusOut`, functional parity with ArduPilot `AP_SBusOut`.

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
| `VRP_SBusOut::init()` | Module initialization |
| `VRP_SBusOut::update()` | Periodic update |

## 6. Verification

See SVCP under `test/libraries/VRP_SBusOut/` and LLRD test list.
