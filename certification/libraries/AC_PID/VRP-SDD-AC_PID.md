# VRP-SDD-AC_PID — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_AC_PID` |
| LLRD | [`VRP-LLRD-AC_PID.yaml`](VRP-LLRD-AC_PID.yaml) |
| DAL | C |
| Status | planned |

## 1. Purpose

Clean-room BSD design for `VRP_AC_PID`, functional parity with ArduPilot `AC_PID`.

## 2. Architecture

_TBD during implementation phase 3._

## 3. Data flow

_TBD — uORB topics / HAL interfaces._

## 4. Safety constraints (DAL C)

- Statement coverage 100%
- Requirements-based tests
- Design review

## 5. Interface summary

| API | Description |
|---|---|
| `VRP_AC_PID::init()` | Module initialization |
| `VRP_AC_PID::update()` | Periodic update |

## 6. Verification

See SVCP under `test/libraries/VRP_AC_PID/` and LLRD test list.
