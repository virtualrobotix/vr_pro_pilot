# VRP-SDD-AP_NavEKF — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_NavEKF` |
| LLRD | [`VRP-LLRD-AP_NavEKF.yaml`](VRP-LLRD-AP_NavEKF.yaml) |
| DAL | B |
| Status | planned |

## 1. Purpose

Clean-room BSD design for `VRP_NavEKF`, functional parity with ArduPilot `AP_NavEKF`.

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
| `VRP_NavEKF::init()` | Module initialization |
| `VRP_NavEKF::update()` | Periodic update |

## 6. Verification

See SVCP under `test/libraries/VRP_NavEKF/` and LLRD test list.
