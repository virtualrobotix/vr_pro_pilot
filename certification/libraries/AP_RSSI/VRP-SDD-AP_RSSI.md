# VRP-SDD-AP_RSSI — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_RSSI` |
| LLRD | [`VRP-LLRD-AP_RSSI.yaml`](VRP-LLRD-AP_RSSI.yaml) |
| DAL | C |
| Status | planned |

## 1. Purpose

Clean-room BSD design for `VRP_RSSI`, functional parity with ArduPilot `AP_RSSI`.

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
| `VRP_RSSI::init()` | Module initialization |
| `VRP_RSSI::update()` | Periodic update |

## 6. Verification

See SVCP under `test/libraries/VRP_RSSI/` and LLRD test list.
