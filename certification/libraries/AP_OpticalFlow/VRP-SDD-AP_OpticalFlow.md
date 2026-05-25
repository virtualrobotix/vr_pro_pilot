# VRP-SDD-AP_OpticalFlow — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_OpticalFlow` |
| LLRD | [`VRP-LLRD-AP_OpticalFlow.yaml`](VRP-LLRD-AP_OpticalFlow.yaml) |
| DAL | C |
| Status | planned |

## 1. Purpose

Clean-room BSD design for `VRP_OpticalFlow`, functional parity with ArduPilot `AP_OpticalFlow`.

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
| `VRP_OpticalFlow::init()` | Module initialization |
| `VRP_OpticalFlow::update()` | Periodic update |

## 6. Verification

See SVCP under `test/libraries/VRP_OpticalFlow/` and LLRD test list.
