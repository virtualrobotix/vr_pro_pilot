# VRP-SDD-AP_Soaring — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_Soaring` |
| LLRD | [`VRP-LLRD-AP_Soaring.yaml`](VRP-LLRD-AP_Soaring.yaml) |
| DAL | C |
| Status | planned |

## 1. Purpose

Clean-room BSD design for `VRP_Soaring`, functional parity with ArduPilot `AP_Soaring`.

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
| `VRP_Soaring::init()` | Module initialization |
| `VRP_Soaring::update()` | Periodic update |

## 6. Verification

See SVCP under `test/libraries/VRP_Soaring/` and LLRD test list.
