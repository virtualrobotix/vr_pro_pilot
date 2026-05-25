# VRP-SDD-AP_SmartRTL — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_SmartRTL` |
| LLRD | [`VRP-LLRD-AP_SmartRTL.yaml`](VRP-LLRD-AP_SmartRTL.yaml) |
| DAL | B |
| Status | planned |

## 1. Purpose

Clean-room BSD design for `VRP_SmartRTL`, functional parity with ArduPilot `AP_SmartRTL`.

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
| `VRP_SmartRTL::init()` | Module initialization |
| `VRP_SmartRTL::update()` | Periodic update |

## 6. Verification

See SVCP under `test/libraries/VRP_SmartRTL/` and LLRD test list.
