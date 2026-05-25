# VRP-SDD-AP_AdvancedFailsafe — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_AdvancedFailsafe` |
| LLRD | [`VRP-LLRD-AP_AdvancedFailsafe.yaml`](VRP-LLRD-AP_AdvancedFailsafe.yaml) |
| DAL | B |
| Status | planned |

## 1. Purpose

Clean-room BSD design for `VRP_AdvancedFailsafe`, functional parity with ArduPilot `AP_AdvancedFailsafe`.

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
| `VRP_AdvancedFailsafe::init()` | Module initialization |
| `VRP_AdvancedFailsafe::update()` | Periodic update |

## 6. Verification

See SVCP under `test/libraries/VRP_AdvancedFailsafe/` and LLRD test list.
