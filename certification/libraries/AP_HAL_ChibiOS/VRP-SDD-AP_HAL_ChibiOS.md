# VRP-SDD-AP_HAL_ChibiOS — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_HAL_ChibiOS` |
| LLRD | [`VRP-LLRD-AP_HAL_ChibiOS.yaml`](VRP-LLRD-AP_HAL_ChibiOS.yaml) |
| DAL | B |
| Status | present |

## 1. Purpose

Clean-room BSD design for `VRP_HAL_ChibiOS`, functional parity with ArduPilot `AP_HAL_ChibiOS`.

## 2. Architecture

_TBD during implementation phase 0._

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
| `VRP_HAL_ChibiOS::init()` | Module initialization |
| `VRP_HAL_ChibiOS::update()` | Periodic update |

## 6. Verification

See SVCP under `test/libraries/VRP_HAL_ChibiOS/` and LLRD test list.
