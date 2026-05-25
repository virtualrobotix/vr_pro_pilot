# VRP-SDD-AP_HAL_Linux — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_HAL_Linux` |
| LLRD | [`VRP-LLRD-AP_HAL_Linux.yaml`](VRP-LLRD-AP_HAL_Linux.yaml) |
| DAL | E |
| Status | planned |

## 1. Purpose

Clean-room BSD design for `VRP_HAL_Linux`, functional parity with ArduPilot `AP_HAL_Linux`.

## 2. Architecture

_TBD during implementation phase 3._

## 3. Data flow

_TBD — uORB topics / HAL interfaces._

## 4. Safety constraints (DAL E)

- Smoke tests
- Best-effort review

## 5. Interface summary

| API | Description |
|---|---|
| `VRP_HAL_Linux::init()` | Module initialization |
| `VRP_HAL_Linux::update()` | Periodic update |

## 6. Verification

See SVCP under `test/libraries/VRP_HAL_Linux/` and LLRD test list.
