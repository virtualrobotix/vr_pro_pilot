# VRP-SDD-AP_Common — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_Common` |
| LLRD | [`VRP-LLRD-AP_Common.yaml`](VRP-LLRD-AP_Common.yaml) |
| DAL | B |
| Status | planned |

## 1. Purpose

Clean-room BSD design for `VRP_Common`, functional parity with ArduPilot `AP_Common`.

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
| `VRP_Common::init()` | Module initialization |
| `VRP_Common::update()` | Periodic update |

## 6. Verification

See SVCP under `test/libraries/VRP_Common/` and LLRD test list.
