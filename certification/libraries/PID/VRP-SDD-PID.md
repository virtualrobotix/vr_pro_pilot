# VRP-SDD-PID — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_PID` |
| LLRD | [`VRP-LLRD-PID.yaml`](VRP-LLRD-PID.yaml) |
| DAL | B |
| Status | planned |

## 1. Purpose

Clean-room BSD design for `VRP_PID`, functional parity with ArduPilot `PID`.

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
| `VRP_PID::init()` | Module initialization |
| `VRP_PID::update()` | Periodic update |

## 6. Verification

See SVCP under `test/libraries/VRP_PID/` and LLRD test list.
