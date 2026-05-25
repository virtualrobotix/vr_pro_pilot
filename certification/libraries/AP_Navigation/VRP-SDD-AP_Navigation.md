# VRP-SDD-AP_Navigation — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_Navigation` |
| LLRD | [`VRP-LLRD-AP_Navigation.yaml`](VRP-LLRD-AP_Navigation.yaml) |
| DAL | C |
| Status | planned |

## 1. Purpose

Clean-room BSD design for `VRP_Navigation`, functional parity with ArduPilot `AP_Navigation`.

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
| `VRP_Navigation::init()` | Module initialization |
| `VRP_Navigation::update()` | Periodic update |

## 6. Verification

See SVCP under `test/libraries/VRP_Navigation/` and LLRD test list.
