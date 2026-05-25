# VRP-SDD-AP_OLC — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_OLC` |
| LLRD | [`VRP-LLRD-AP_OLC.yaml`](VRP-LLRD-AP_OLC.yaml) |
| DAL | C |
| Status | planned |

## 1. Purpose

Clean-room BSD design for `VRP_OLC`, functional parity with ArduPilot `AP_OLC`.

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
| `VRP_OLC::init()` | Module initialization |
| `VRP_OLC::update()` | Periodic update |

## 6. Verification

See SVCP under `test/libraries/VRP_OLC/` and LLRD test list.
