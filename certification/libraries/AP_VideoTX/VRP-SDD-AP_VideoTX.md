# VRP-SDD-AP_VideoTX — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_VideoTX` |
| LLRD | [`VRP-LLRD-AP_VideoTX.yaml`](VRP-LLRD-AP_VideoTX.yaml) |
| DAL | E |
| Status | planned |

## 1. Purpose

Clean-room BSD design for `VRP_VideoTX`, functional parity with ArduPilot `AP_VideoTX`.

## 2. Architecture

_TBD during implementation phase 3._

## 3. Data flow

_TBD — uORB topics / HAL interfaces._

## 4. Safety constraints (DAL E)

- Smoke tests
- Best-effort review

## 5. Interface summary

| API | Description |
|---|---|
| `VRP_VideoTX::init()` | Module initialization |
| `VRP_VideoTX::update()` | Periodic update |

## 6. Verification

See SVCP under `test/libraries/VRP_VideoTX/` and LLRD test list.
