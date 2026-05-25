# VRP-SDD-AP_OpenDroneID — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_OpenDroneID` |
| LLRD | [`VRP-LLRD-AP_OpenDroneID.yaml`](VRP-LLRD-AP_OpenDroneID.yaml) |
| DAL | C |
| Status | planned |

## 1. Purpose

Clean-room BSD design for `VRP_OpenDroneID`, functional parity with ArduPilot `AP_OpenDroneID`.

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
| `VRP_OpenDroneID::init()` | Module initialization |
| `VRP_OpenDroneID::update()` | Periodic update |

## 6. Verification

See SVCP under `test/libraries/VRP_OpenDroneID/` and LLRD test list.
