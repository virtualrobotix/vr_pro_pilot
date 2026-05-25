# VRP-SDD-AP_Mount — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_Mount` |
| LLRD | [`VRP-LLRD-AP_Mount.yaml`](VRP-LLRD-AP_Mount.yaml) |
| DAL | C |
| Status | planned |

## 1. Purpose

Clean-room BSD design for `VRP_Mount`, functional parity with ArduPilot `AP_Mount`.

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
| `VRP_Mount::init()` | Module initialization |
| `VRP_Mount::update()` | Periodic update |

## 6. Verification

See SVCP under `test/libraries/VRP_Mount/` and LLRD test list.
