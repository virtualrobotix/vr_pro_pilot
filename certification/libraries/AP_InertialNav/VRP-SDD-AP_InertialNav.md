# VRP-SDD-AP_InertialNav — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_InertialNav` |
| LLRD | [`VRP-LLRD-AP_InertialNav.yaml`](VRP-LLRD-AP_InertialNav.yaml) |
| DAL | B |
| Status | planned |

## 1. Purpose

Clean-room BSD design for `VRP_InertialNav`, functional parity with ArduPilot `AP_InertialNav`.

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
| `VRP_InertialNav::init()` | Module initialization |
| `VRP_InertialNav::update()` | Periodic update |

## 6. Verification

See SVCP under `test/libraries/VRP_InertialNav/` and LLRD test list.
