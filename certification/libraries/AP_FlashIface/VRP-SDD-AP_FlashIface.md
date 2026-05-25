# VRP-SDD-AP_FlashIface — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_FlashIface` |
| LLRD | [`VRP-LLRD-AP_FlashIface.yaml`](VRP-LLRD-AP_FlashIface.yaml) |
| DAL | C |
| Status | planned |

## 1. Purpose

Clean-room BSD design for `VRP_FlashIface`, functional parity with ArduPilot `AP_FlashIface`.

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
| `VRP_FlashIface::init()` | Module initialization |
| `VRP_FlashIface::update()` | Periodic update |

## 6. Verification

See SVCP under `test/libraries/VRP_FlashIface/` and LLRD test list.
