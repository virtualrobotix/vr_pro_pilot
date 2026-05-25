# VRP-SDD-AP_Parachute — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_Parachute` |
| LLRD | [`VRP-LLRD-AP_Parachute.yaml`](VRP-LLRD-AP_Parachute.yaml) |
| DAL | B |
| Status | planned |

## 1. Purpose

Clean-room BSD design for `VRP_Parachute`, functional parity with ArduPilot `AP_Parachute`.

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
| `VRP_Parachute::init()` | Module initialization |
| `VRP_Parachute::update()` | Periodic update |

## 6. Verification

See SVCP under `test/libraries/VRP_Parachute/` and LLRD test list.
