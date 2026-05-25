# VRP-SDD-AP_AIS — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_AIS` |
| LLRD | [`VRP-LLRD-AP_AIS.yaml`](VRP-LLRD-AP_AIS.yaml) |
| DAL | C |
| Status | planned |

## 1. Purpose

Clean-room BSD design for `VRP_AIS`, functional parity with ArduPilot `AP_AIS`.

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
| `VRP_AIS::init()` | Module initialization |
| `VRP_AIS::update()` | Periodic update |

## 6. Verification

See SVCP under `test/libraries/VRP_AIS/` and LLRD test list.
