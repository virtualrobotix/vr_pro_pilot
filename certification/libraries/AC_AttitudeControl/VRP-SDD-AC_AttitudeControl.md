# VRP-SDD-AC_AttitudeControl — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_AC_AttitudeControl` |
| LLRD | [`VRP-LLRD-AC_AttitudeControl.yaml`](VRP-LLRD-AC_AttitudeControl.yaml) |
| DAL | B |
| Status | planned |

## 1. Purpose

Clean-room BSD design for `VRP_AC_AttitudeControl`, functional parity with ArduPilot `AC_AttitudeControl`.

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
| `VRP_AC_AttitudeControl::init()` | Module initialization |
| `VRP_AC_AttitudeControl::update()` | Periodic update |

## 6. Verification

See SVCP under `test/libraries/VRP_AC_AttitudeControl/` and LLRD test list.
