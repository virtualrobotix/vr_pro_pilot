# VRP-SDD-AP_NavEKF2 — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_NavEKF2` |
| LLRD | [`VRP-LLRD-AP_NavEKF2.yaml`](VRP-LLRD-AP_NavEKF2.yaml) |
| DAL | B |
| Status | partial |

## 1. Purpose

Clean-room BSD design for `VRP_NavEKF2`, functional parity with ArduPilot `AP_NavEKF2`.

## 2. Architecture

_TBD during implementation phase 1._

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
| `VRP_NavEKF2::init()` | Module initialization |
| `VRP_NavEKF2::update()` | Periodic update |

## 6. Verification

See SVCP under `test/libraries/VRP_NavEKF2/` and LLRD test list.
