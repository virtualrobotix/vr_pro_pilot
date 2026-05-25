# VRP-SDD-AP_DDS — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_DDS` |
| LLRD | [`VRP-LLRD-AP_DDS.yaml`](VRP-LLRD-AP_DDS.yaml) |
| DAL | C |
| Status | partial |

## 1. Purpose

Clean-room BSD design for `VRP_DDS`, functional parity with ArduPilot `AP_DDS`.

## 2. Architecture

_TBD during implementation phase 2._

## 3. Data flow

_TBD — uORB topics / HAL interfaces._

## 4. Safety constraints (DAL C)

- Statement coverage 100%
- Requirements-based tests
- Design review

## 5. Interface summary

| API | Description |
|---|---|
| `VRP_DDS::init()` | Module initialization |
| `VRP_DDS::update()` | Periodic update |

## 6. Verification

See SVCP under `test/libraries/VRP_DDS/` and LLRD test list.
