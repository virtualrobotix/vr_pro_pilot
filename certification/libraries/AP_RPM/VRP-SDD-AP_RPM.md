# VRP-SDD-AP_RPM — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_RPM` |
| LLRD | [`VRP-LLRD-AP_RPM.yaml`](VRP-LLRD-AP_RPM.yaml) |
| DAL | C |
| Status | planned |

## 1. Purpose

Clean-room BSD design for `VRP_RPM`, functional parity with ArduPilot `AP_RPM`.

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
| `VRP_RPM::init()` | Module initialization |
| `VRP_RPM::update()` | Periodic update |

## 6. Verification

See SVCP under `test/libraries/VRP_RPM/` and LLRD test list.
