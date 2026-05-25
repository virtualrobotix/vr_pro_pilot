# VRP-SDD-AP_Avoidance — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_Avoidance` |
| LLRD | [`VRP-LLRD-AP_Avoidance.yaml`](VRP-LLRD-AP_Avoidance.yaml) |
| DAL | B |
| Status | planned |

## 1. Purpose

Clean-room BSD design for `VRP_Avoidance`, functional parity with ArduPilot `AP_Avoidance`.

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
| `VRP_Avoidance::init()` | Module initialization |
| `VRP_Avoidance::update()` | Periodic update |

## 6. Verification

See SVCP under `test/libraries/VRP_Avoidance/` and LLRD test list.
