# VRP-SDD-AP_Math — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_Math` |
| LLRD | [`VRP-LLRD-AP_Math.yaml`](VRP-LLRD-AP_Math.yaml) |
| DAL | B |
| Status | planned |

## 1. Purpose

Clean-room BSD design for `VRP_Math`, functional parity with ArduPilot `AP_Math`.

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
| `VRP_Math::init()` | Module initialization |
| `VRP_Math::update()` | Periodic update |

## 6. Verification

See SVCP under `test/libraries/VRP_Math/` and LLRD test list.
