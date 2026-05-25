# VRP-SDD-AP_InertialSensor — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_InertialSensor` |
| LLRD | [`VRP-LLRD-AP_InertialSensor.yaml`](VRP-LLRD-AP_InertialSensor.yaml) |
| DAL | B |
| Status | planned |

## 1. Purpose

Clean-room BSD design for `VRP_InertialSensor`, functional parity with ArduPilot `AP_InertialSensor`.

## 2. Architecture

_TBD during implementation phase 3._

## 3. Data flow

_TBD — uORB topics / HAL interfaces._

## 4. Safety constraints (DAL B)

- MC/DC on safety paths
- No dynamic heap
- Bounded WCET
- MISRA subset

## 5. Interface summary

| API | Description |
|---|---|
| `VRP_InertialSensor::init()` | Module initialization |
| `VRP_InertialSensor::update()` | Periodic update |

## 6. Verification

See SVCP under `test/libraries/VRP_InertialSensor/` and LLRD test list.
