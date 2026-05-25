# VRP-SDD-AC_Fence — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_AC_Fence` |
| LLRD | [`VRP-LLRD-AC_Fence.yaml`](VRP-LLRD-AC_Fence.yaml) |
| DAL | B |
| Status | planned |

## 1. Purpose

Clean-room BSD design for `VRP_AC_Fence`, functional parity with ArduPilot `AC_Fence`.

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
| `VRP_AC_Fence::init()` | Module initialization |
| `VRP_AC_Fence::update()` | Periodic update |

## 6. Verification

See SVCP under `test/libraries/VRP_AC_Fence/` and LLRD test list.
