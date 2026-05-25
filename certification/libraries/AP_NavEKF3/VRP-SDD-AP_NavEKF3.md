# VRP-SDD-AP_NavEKF3 — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_NavEKF3` |
| LLRD | [`VRP-LLRD-AP_NavEKF3.yaml`](VRP-LLRD-AP_NavEKF3.yaml) |
| DAL | B |
| Status | planned |

## 1. Purpose

Clean-room BSD design for `VRP_NavEKF3`, functional parity with ArduPilot `AP_NavEKF3`.

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
| `VRP_NavEKF3::init()` | Module initialization |
| `VRP_NavEKF3::update()` | Periodic update |

## 6. Verification

See SVCP under `test/libraries/VRP_NavEKF3/` and LLRD test list.
