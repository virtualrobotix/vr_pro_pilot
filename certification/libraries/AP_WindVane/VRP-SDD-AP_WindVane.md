# VRP-SDD-AP_WindVane — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_WindVane` |
| LLRD | [`VRP-LLRD-AP_WindVane.yaml`](VRP-LLRD-AP_WindVane.yaml) |
| DAL | C |
| Status | planned |

## 1. Purpose

Clean-room BSD design for `VRP_WindVane`, functional parity with ArduPilot `AP_WindVane`.

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
| `VRP_WindVane::init()` | Module initialization |
| `VRP_WindVane::update()` | Periodic update |

## 6. Verification

See SVCP under `test/libraries/VRP_WindVane/` and LLRD test list.
