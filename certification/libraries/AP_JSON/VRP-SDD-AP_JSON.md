# VRP-SDD-AP_JSON — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_JSON` |
| LLRD | [`VRP-LLRD-AP_JSON.yaml`](VRP-LLRD-AP_JSON.yaml) |
| DAL | C |
| Status | planned |

## 1. Purpose

Clean-room BSD design for `VRP_JSON`, functional parity with ArduPilot `AP_JSON`.

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
| `VRP_JSON::init()` | Module initialization |
| `VRP_JSON::update()` | Periodic update |

## 6. Verification

See SVCP under `test/libraries/VRP_JSON/` and LLRD test list.
