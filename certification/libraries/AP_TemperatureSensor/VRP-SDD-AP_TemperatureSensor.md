# VRP-SDD-AP_TemperatureSensor — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_TemperatureSensor` |
| LLRD | [`VRP-LLRD-AP_TemperatureSensor.yaml`](VRP-LLRD-AP_TemperatureSensor.yaml) |
| DAL | C |
| Status | planned |

## 1. Purpose

Clean-room BSD design for `VRP_TemperatureSensor`, functional parity with ArduPilot `AP_TemperatureSensor`.

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
| `VRP_TemperatureSensor::init()` | Module initialization |
| `VRP_TemperatureSensor::update()` | Periodic update |

## 6. Verification

See SVCP under `test/libraries/VRP_TemperatureSensor/` and LLRD test list.
