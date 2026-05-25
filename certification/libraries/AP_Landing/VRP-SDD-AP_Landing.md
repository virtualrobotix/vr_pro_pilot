# VRP-SDD-AP_Landing — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_Landing` |
| LLRD | [`VRP-LLRD-AP_Landing.yaml`](VRP-LLRD-AP_Landing.yaml) |
| DAL | B |
| Status | planned |

## 1. Purpose

Clean-room BSD design for `VRP_Landing`, functional parity with ArduPilot `AP_Landing`.

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
| `VRP_Landing::init()` | Module initialization |
| `VRP_Landing::update()` | Periodic update |

## 6. Verification

See SVCP under `test/libraries/VRP_Landing/` and LLRD test list.
