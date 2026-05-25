# VRP-SDD-AP_ExternalControl — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_ExternalControl` |
| LLRD | [`VRP-LLRD-AP_ExternalControl.yaml`](VRP-LLRD-AP_ExternalControl.yaml) |
| DAL | C |
| Status | planned |

## 1. Purpose

Clean-room BSD design for `VRP_ExternalControl`, functional parity with ArduPilot `AP_ExternalControl`.

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
| `VRP_ExternalControl::init()` | Module initialization |
| `VRP_ExternalControl::update()` | Periodic update |

## 6. Verification

See SVCP under `test/libraries/VRP_ExternalControl/` and LLRD test list.
