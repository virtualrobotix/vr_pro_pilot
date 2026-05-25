# VRP-SDD-AP_Radio — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_Radio` |
| LLRD | [`VRP-LLRD-AP_Radio.yaml`](VRP-LLRD-AP_Radio.yaml) |
| DAL | C |
| Status | planned |

## 1. Purpose

Clean-room BSD design for `VRP_Radio`, functional parity with ArduPilot `AP_Radio`.

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
| `VRP_Radio::init()` | Module initialization |
| `VRP_Radio::update()` | Periodic update |

## 6. Verification

See SVCP under `test/libraries/VRP_Radio/` and LLRD test list.
