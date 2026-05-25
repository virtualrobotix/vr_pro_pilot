# VRP-SDD-AP_DAC — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_DAC` |
| LLRD | [`VRP-LLRD-AP_DAC.yaml`](VRP-LLRD-AP_DAC.yaml) |
| DAL | C |
| Status | planned |

## 1. Purpose

Clean-room BSD design for `VRP_DAC`, functional parity with ArduPilot `AP_DAC`.

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
| `VRP_DAC::init()` | Module initialization |
| `VRP_DAC::update()` | Periodic update |

## 6. Verification

See SVCP under `test/libraries/VRP_DAC/` and LLRD test list.
