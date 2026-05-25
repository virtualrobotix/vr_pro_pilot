# VRP-SDD-AP_LightWareSerial — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_LightWareSerial` |
| LLRD | [`VRP-LLRD-AP_LightWareSerial.yaml`](VRP-LLRD-AP_LightWareSerial.yaml) |
| DAL | C |
| Status | planned |

## 1. Purpose

Clean-room BSD design for `VRP_LightWareSerial`, functional parity with ArduPilot `AP_LightWareSerial`.

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
| `VRP_LightWareSerial::init()` | Module initialization |
| `VRP_LightWareSerial::update()` | Periodic update |

## 6. Verification

See SVCP under `test/libraries/VRP_LightWareSerial/` and LLRD test list.
