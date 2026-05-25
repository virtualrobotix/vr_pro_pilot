# VRP-SDD-AP_Camera — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_Camera` |
| LLRD | [`VRP-LLRD-AP_Camera.yaml`](VRP-LLRD-AP_Camera.yaml) |
| DAL | C |
| Status | planned |

## 1. Purpose

Clean-room BSD design for `VRP_Camera`, functional parity with ArduPilot `AP_Camera`.

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
| `VRP_Camera::init()` | Module initialization |
| `VRP_Camera::update()` | Periodic update |

## 6. Verification

See SVCP under `test/libraries/VRP_Camera/` and LLRD test list.
