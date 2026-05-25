# VRP-SDD-AP_Scheduler — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_Scheduler` |
| LLRD | [`VRP-LLRD-AP_Scheduler.yaml`](VRP-LLRD-AP_Scheduler.yaml) |
| DAL | B |
| Status | partial |

## 1. Purpose

Clean-room BSD design for `VRP_Scheduler`, functional parity with ArduPilot `AP_Scheduler`.

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
| `VRP_Scheduler::init()` | Module initialization |
| `VRP_Scheduler::update()` | Periodic update |

## 6. Verification

See SVCP under `test/libraries/VRP_Scheduler/` and LLRD test list.
