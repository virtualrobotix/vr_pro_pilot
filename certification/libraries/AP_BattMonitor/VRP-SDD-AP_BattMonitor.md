# VRP-SDD-AP_BattMonitor — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_BattMonitor` |
| LLRD | [`VRP-LLRD-AP_BattMonitor.yaml`](VRP-LLRD-AP_BattMonitor.yaml) |
| DAL | B |
| Status | planned |

## 1. Purpose

Clean-room BSD design for `VRP_BattMonitor`, functional parity with ArduPilot `AP_BattMonitor`.

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
| `VRP_BattMonitor::init()` | Module initialization |
| `VRP_BattMonitor::update()` | Periodic update |

## 6. Verification

See SVCP under `test/libraries/VRP_BattMonitor/` and LLRD test list.
