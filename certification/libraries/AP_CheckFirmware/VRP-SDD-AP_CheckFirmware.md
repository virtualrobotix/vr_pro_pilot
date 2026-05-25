# VRP-SDD-AP_CheckFirmware — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_CheckFirmware` |
| LLRD | [`VRP-LLRD-AP_CheckFirmware.yaml`](VRP-LLRD-AP_CheckFirmware.yaml) |
| DAL | B |
| Status | planned |

## 1. Purpose

Clean-room BSD design for `VRP_CheckFirmware`, functional parity with ArduPilot `AP_CheckFirmware`.

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
| `VRP_CheckFirmware::init()` | Module initialization |
| `VRP_CheckFirmware::update()` | Periodic update |

## 6. Verification

See SVCP under `test/libraries/VRP_CheckFirmware/` and LLRD test list.
