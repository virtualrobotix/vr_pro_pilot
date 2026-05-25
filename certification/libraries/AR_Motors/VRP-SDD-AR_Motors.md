# VRP-SDD-AR_Motors — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_AR_Motors` |
| LLRD | [`VRP-LLRD-AR_Motors.yaml`](VRP-LLRD-AR_Motors.yaml) |
| DAL | B |
| Status | planned |

## 1. Purpose

Clean-room BSD design for `VRP_AR_Motors`, functional parity with ArduPilot `AR_Motors`.

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
| `VRP_AR_Motors::init()` | Module initialization |
| `VRP_AR_Motors::update()` | Periodic update |

## 6. Verification

See SVCP under `test/libraries/VRP_AR_Motors/` and LLRD test list.
