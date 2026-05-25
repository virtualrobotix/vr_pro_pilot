# VRP-SDD-AP_RCProtocol — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_RCProtocol` |
| LLRD | [`VRP-LLRD-AP_RCProtocol.yaml`](VRP-LLRD-AP_RCProtocol.yaml) |
| DAL | C |
| Status | planned |

## 1. Purpose

Clean-room BSD design for `VRP_RCProtocol`, functional parity with ArduPilot `AP_RCProtocol`.

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
| `VRP_RCProtocol::init()` | Module initialization |
| `VRP_RCProtocol::update()` | Periodic update |

## 6. Verification

See SVCP under `test/libraries/VRP_RCProtocol/` and LLRD test list.
