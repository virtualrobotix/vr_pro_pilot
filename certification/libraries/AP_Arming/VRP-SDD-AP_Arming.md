# VRP-SDD-AP_Arming — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_Arming` |
| LLRD | [`VRP-LLRD-AP_Arming.yaml`](VRP-LLRD-AP_Arming.yaml) |
| DAL | B |
| Status | planned |

## 1. Purpose

Clean-room BSD design for `VRP_Arming`, functional parity with ArduPilot `AP_Arming`.

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
| `VRP_Arming::init()` | Module initialization |
| `VRP_Arming::update()` | Periodic update |

## 6. Verification

See SVCP under `test/libraries/VRP_Arming/` and LLRD test list.
