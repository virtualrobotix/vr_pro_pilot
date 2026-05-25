# VRP-SDD-AP_Rally — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_Rally` |
| LLRD | [`VRP-LLRD-AP_Rally.yaml`](VRP-LLRD-AP_Rally.yaml) |
| DAL | C |
| Status | planned |

## 1. Purpose

Clean-room BSD design for `VRP_Rally`, functional parity with ArduPilot `AP_Rally`.

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
| `VRP_Rally::init()` | Module initialization |
| `VRP_Rally::update()` | Periodic update |

## 6. Verification

See SVCP under `test/libraries/VRP_Rally/` and LLRD test list.
