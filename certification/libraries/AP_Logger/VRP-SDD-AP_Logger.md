# VRP-SDD-AP_Logger — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_Logger` |
| LLRD | [`VRP-LLRD-AP_Logger.yaml`](VRP-LLRD-AP_Logger.yaml) |
| DAL | B |
| Status | planned |

## 1. Purpose

Clean-room BSD design for `VRP_Logger`, functional parity with ArduPilot `AP_Logger`.

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
| `VRP_Logger::init()` | Module initialization |
| `VRP_Logger::update()` | Periodic update |

## 6. Verification

See SVCP under `test/libraries/VRP_Logger/` and LLRD test list.
