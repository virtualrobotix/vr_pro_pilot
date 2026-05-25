# VRP-SDD-AP_Param — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_Param` |
| LLRD | [`VRP-LLRD-AP_Param.yaml`](VRP-LLRD-AP_Param.yaml) |
| DAL | B |
| Status | partial |

## 1. Purpose

Clean-room BSD design for `VRP_Param`, functional parity with ArduPilot `AP_Param`.

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
| `VRP_Param::init()` | Module initialization |
| `VRP_Param::update()` | Periodic update |

## 6. Verification

See SVCP under `test/libraries/VRP_Param/` and LLRD test list.
