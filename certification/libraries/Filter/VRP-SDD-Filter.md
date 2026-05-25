# VRP-SDD-Filter — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_Filter` |
| LLRD | [`VRP-LLRD-Filter.yaml`](VRP-LLRD-Filter.yaml) |
| DAL | B |
| Status | planned |

## 1. Purpose

Clean-room BSD design for `VRP_Filter`, functional parity with ArduPilot `Filter`.

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
| `VRP_Filter::init()` | Module initialization |
| `VRP_Filter::update()` | Periodic update |

## 6. Verification

See SVCP under `test/libraries/VRP_Filter/` and LLRD test list.
