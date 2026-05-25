# VRP-SDD-AP_Beacon — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_Beacon` |
| LLRD | [`VRP-LLRD-AP_Beacon.yaml`](VRP-LLRD-AP_Beacon.yaml) |
| DAL | C |
| Status | planned |

## 1. Purpose

Clean-room BSD design for `VRP_Beacon`, functional parity with ArduPilot `AP_Beacon`.

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
| `VRP_Beacon::init()` | Module initialization |
| `VRP_Beacon::update()` | Periodic update |

## 6. Verification

See SVCP under `test/libraries/VRP_Beacon/` and LLRD test list.
