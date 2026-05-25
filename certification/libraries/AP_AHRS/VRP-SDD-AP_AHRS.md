# VRP-SDD-AP_AHRS — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_AHRS` |
| LLRD | [`VRP-LLRD-AP_AHRS.yaml`](VRP-LLRD-AP_AHRS.yaml) |
| DAL | B |
| Status | planned |

## 1. Purpose

Clean-room BSD design for `VRP_AHRS`, functional parity with ArduPilot `AP_AHRS`.

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
| `VRP_AHRS::init()` | Module initialization |
| `VRP_AHRS::update()` | Periodic update |

## 6. Verification

See SVCP under `test/libraries/VRP_AHRS/` and LLRD test list.
