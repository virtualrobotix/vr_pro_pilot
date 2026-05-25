# VRP-SDD-AP_Airspeed — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_Airspeed` |
| LLRD | [`VRP-LLRD-AP_Airspeed.yaml`](VRP-LLRD-AP_Airspeed.yaml) |
| DAL | B |
| Status | planned |

## 1. Purpose

Clean-room BSD design for `VRP_Airspeed`, functional parity with ArduPilot `AP_Airspeed`.

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
| `VRP_Airspeed::init()` | Module initialization |
| `VRP_Airspeed::update()` | Periodic update |

## 6. Verification

See SVCP under `test/libraries/VRP_Airspeed/` and LLRD test list.
