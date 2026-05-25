# VRP-SDD-AP_RAMTRON — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_RAMTRON` |
| LLRD | [`VRP-LLRD-AP_RAMTRON.yaml`](VRP-LLRD-AP_RAMTRON.yaml) |
| DAL | C |
| Status | planned |

## 1. Purpose

Clean-room BSD design for `VRP_RAMTRON`, functional parity with ArduPilot `AP_RAMTRON`.

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
| `VRP_RAMTRON::init()` | Module initialization |
| `VRP_RAMTRON::update()` | Periodic update |

## 6. Verification

See SVCP under `test/libraries/VRP_RAMTRON/` and LLRD test list.
