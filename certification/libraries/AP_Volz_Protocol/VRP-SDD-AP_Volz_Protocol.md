# VRP-SDD-AP_Volz_Protocol — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_Volz_Protocol` |
| LLRD | [`VRP-LLRD-AP_Volz_Protocol.yaml`](VRP-LLRD-AP_Volz_Protocol.yaml) |
| DAL | C |
| Status | planned |

## 1. Purpose

Clean-room BSD design for `VRP_Volz_Protocol`, functional parity with ArduPilot `AP_Volz_Protocol`.

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
| `VRP_Volz_Protocol::init()` | Module initialization |
| `VRP_Volz_Protocol::update()` | Periodic update |

## 6. Verification

See SVCP under `test/libraries/VRP_Volz_Protocol/` and LLRD test list.
