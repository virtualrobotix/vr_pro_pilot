# VRP-SDD-AP_Vehicle — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_Vehicle` |
| LLRD | [`VRP-LLRD-AP_Vehicle.yaml`](VRP-LLRD-AP_Vehicle.yaml) |
| DAL | B |
| Status | partial |

## 1. Purpose

Clean-room BSD design for `VRP_Vehicle`, functional parity with ArduPilot `AP_Vehicle`.

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
| `VRP_Vehicle::init()` | Module initialization |
| `VRP_Vehicle::update()` | Periodic update |

## 6. Verification

See SVCP under `test/libraries/VRP_Vehicle/` and LLRD test list.
