# VRP-SDD-AP_Generator — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_Generator` |
| LLRD | [`VRP-LLRD-AP_Generator.yaml`](VRP-LLRD-AP_Generator.yaml) |
| DAL | C |
| Status | planned |

## 1. Purpose

Clean-room BSD design for `VRP_Generator`, functional parity with ArduPilot `AP_Generator`.

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
| `VRP_Generator::init()` | Module initialization |
| `VRP_Generator::update()` | Periodic update |

## 6. Verification

See SVCP under `test/libraries/VRP_Generator/` and LLRD test list.
