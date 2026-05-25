# VRP-SDD-AP_SerialLED — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_SerialLED` |
| LLRD | [`VRP-LLRD-AP_SerialLED.yaml`](VRP-LLRD-AP_SerialLED.yaml) |
| DAL | C |
| Status | planned |

## 1. Purpose

Clean-room BSD design for `VRP_SerialLED`, functional parity with ArduPilot `AP_SerialLED`.

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
| `VRP_SerialLED::init()` | Module initialization |
| `VRP_SerialLED::update()` | Periodic update |

## 6. Verification

See SVCP under `test/libraries/VRP_SerialLED/` and LLRD test list.
