# VRP-SDD-AP_Relay — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_Relay` |
| LLRD | [`VRP-LLRD-AP_Relay.yaml`](VRP-LLRD-AP_Relay.yaml) |
| DAL | C |
| Status | planned |

## 1. Purpose

Clean-room BSD design for `VRP_Relay`, functional parity with ArduPilot `AP_Relay`.

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
| `VRP_Relay::init()` | Module initialization |
| `VRP_Relay::update()` | Periodic update |

## 6. Verification

See SVCP under `test/libraries/VRP_Relay/` and LLRD test list.
