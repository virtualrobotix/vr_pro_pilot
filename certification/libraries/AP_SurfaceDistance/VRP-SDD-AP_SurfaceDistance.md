# VRP-SDD-AP_SurfaceDistance — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_SurfaceDistance` |
| LLRD | [`VRP-LLRD-AP_SurfaceDistance.yaml`](VRP-LLRD-AP_SurfaceDistance.yaml) |
| DAL | C |
| Status | planned |

## 1. Purpose

Clean-room BSD design for `VRP_SurfaceDistance`, functional parity with ArduPilot `AP_SurfaceDistance`.

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
| `VRP_SurfaceDistance::init()` | Module initialization |
| `VRP_SurfaceDistance::update()` | Periodic update |

## 6. Verification

See SVCP under `test/libraries/VRP_SurfaceDistance/` and LLRD test list.
