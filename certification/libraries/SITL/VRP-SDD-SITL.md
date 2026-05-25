# VRP-SDD-SITL — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_SITL` |
| LLRD | [`VRP-LLRD-SITL.yaml`](VRP-LLRD-SITL.yaml) |
| DAL | C |
| Status | partial |

## 1. Purpose

Clean-room BSD design for `VRP_SITL`, functional parity with ArduPilot `SITL`.

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
| `VRP_SITL::init()` | Module initialization |
| `VRP_SITL::update()` | Periodic update |

## 6. Verification

See SVCP under `test/libraries/VRP_SITL/` and LLRD test list.
