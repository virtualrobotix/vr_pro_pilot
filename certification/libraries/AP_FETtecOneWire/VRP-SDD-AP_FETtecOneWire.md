# VRP-SDD-AP_FETtecOneWire — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_FETtecOneWire` |
| LLRD | [`VRP-LLRD-AP_FETtecOneWire.yaml`](VRP-LLRD-AP_FETtecOneWire.yaml) |
| DAL | C |
| Status | planned |

## 1. Purpose

Clean-room BSD design for `VRP_FETtecOneWire`, functional parity with ArduPilot `AP_FETtecOneWire`.

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
| `VRP_FETtecOneWire::init()` | Module initialization |
| `VRP_FETtecOneWire::update()` | Periodic update |

## 6. Verification

See SVCP under `test/libraries/VRP_FETtecOneWire/` and LLRD test list.
