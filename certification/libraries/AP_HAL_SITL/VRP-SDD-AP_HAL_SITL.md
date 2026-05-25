# VRP-SDD-AP_HAL_SITL — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_HAL_SITL` |
| LLRD | [`VRP-LLRD-AP_HAL_SITL.yaml`](VRP-LLRD-AP_HAL_SITL.yaml) |
| DAL | C |
| Status | present |

## 1. Purpose

Clean-room BSD design for `VRP_HAL_SITL`, functional parity with ArduPilot `AP_HAL_SITL`.

## 2. Architecture

_TBD during implementation phase 0._

## 3. Data flow

_TBD — uORB topics / HAL interfaces._

## 4. Safety constraints (DAL C)

- Statement coverage 100%
- Requirements-based tests
- Design review

## 5. Interface summary

| API | Description |
|---|---|
| `VRP_HAL_SITL::init()` | Module initialization |
| `VRP_HAL_SITL::update()` | Periodic update |

## 6. Verification

See SVCP under `test/libraries/VRP_HAL_SITL/` and LLRD test list.
