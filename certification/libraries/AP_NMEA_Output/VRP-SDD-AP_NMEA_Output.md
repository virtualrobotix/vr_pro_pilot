# VRP-SDD-AP_NMEA_Output — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_NMEA_Output` |
| LLRD | [`VRP-LLRD-AP_NMEA_Output.yaml`](VRP-LLRD-AP_NMEA_Output.yaml) |
| DAL | C |
| Status | planned |

## 1. Purpose

Clean-room BSD design for `VRP_NMEA_Output`, functional parity with ArduPilot `AP_NMEA_Output`.

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
| `VRP_NMEA_Output::init()` | Module initialization |
| `VRP_NMEA_Output::update()` | Periodic update |

## 6. Verification

See SVCP under `test/libraries/VRP_NMEA_Output/` and LLRD test list.
