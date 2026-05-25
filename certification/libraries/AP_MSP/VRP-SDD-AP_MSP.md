# VRP-SDD-AP_MSP — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_MSP` |
| LLRD | [`VRP-LLRD-AP_MSP.yaml`](VRP-LLRD-AP_MSP.yaml) |
| DAL | C |
| Status | planned |

## 1. Purpose

Clean-room BSD design for `VRP_MSP`, functional parity with ArduPilot `AP_MSP`.

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
| `VRP_MSP::init()` | Module initialization |
| `VRP_MSP::update()` | Periodic update |

## 6. Verification

See SVCP under `test/libraries/VRP_MSP/` and LLRD test list.
