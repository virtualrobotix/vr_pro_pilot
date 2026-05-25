# VRP-SDD-AP_L1_Control — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_L1_Control` |
| LLRD | [`VRP-LLRD-AP_L1_Control.yaml`](VRP-LLRD-AP_L1_Control.yaml) |
| DAL | B |
| Status | planned |

## 1. Purpose

Clean-room BSD design for `VRP_L1_Control`, functional parity with ArduPilot `AP_L1_Control`.

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
| `VRP_L1_Control::init()` | Module initialization |
| `VRP_L1_Control::update()` | Periodic update |

## 6. Verification

See SVCP under `test/libraries/VRP_L1_Control/` and LLRD test list.
