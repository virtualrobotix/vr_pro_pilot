# VRP-SDD-AP_CustomRotations — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_CustomRotations` |
| LLRD | [`VRP-LLRD-AP_CustomRotations.yaml`](VRP-LLRD-AP_CustomRotations.yaml) |
| DAL | C |
| Status | planned |

## 1. Purpose

Clean-room BSD design for `VRP_CustomRotations`, functional parity with ArduPilot `AP_CustomRotations`.

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
| `VRP_CustomRotations::init()` | Module initialization |
| `VRP_CustomRotations::update()` | Periodic update |

## 6. Verification

See SVCP under `test/libraries/VRP_CustomRotations/` and LLRD test list.
