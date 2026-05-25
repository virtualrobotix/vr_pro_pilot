# VRP-SDD-AP_Compass — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_Compass` |
| LLRD | [`VRP-LLRD-AP_Compass.yaml`](VRP-LLRD-AP_Compass.yaml) |
| DAL | B |
| Status | planned |

## 1. Purpose

Clean-room BSD design for `VRP_Compass`, functional parity with ArduPilot `AP_Compass`.

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
| `VRP_Compass::init()` | Module initialization |
| `VRP_Compass::update()` | Periodic update |

## 6. Verification

See SVCP under `test/libraries/VRP_Compass/` and LLRD test list.
