# VRP-SDD-AP_Mission — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_Mission` |
| LLRD | [`VRP-LLRD-AP_Mission.yaml`](VRP-LLRD-AP_Mission.yaml) |
| DAL | B |
| Status | planned |

## 1. Purpose

Clean-room BSD design for `VRP_Mission`, functional parity with ArduPilot `AP_Mission`.

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
| `VRP_Mission::init()` | Module initialization |
| `VRP_Mission::update()` | Periodic update |

## 6. Verification

See SVCP under `test/libraries/VRP_Mission/` and LLRD test list.
