# VRP-SDD-AP_ExternalAHRS — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_ExternalAHRS` |
| LLRD | [`VRP-LLRD-AP_ExternalAHRS.yaml`](VRP-LLRD-AP_ExternalAHRS.yaml) |
| DAL | B |
| Status | planned |

## 1. Purpose

Clean-room BSD design for `VRP_ExternalAHRS`, functional parity with ArduPilot `AP_ExternalAHRS`.

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
| `VRP_ExternalAHRS::init()` | Module initialization |
| `VRP_ExternalAHRS::update()` | Periodic update |

## 6. Verification

See SVCP under `test/libraries/VRP_ExternalAHRS/` and LLRD test list.
