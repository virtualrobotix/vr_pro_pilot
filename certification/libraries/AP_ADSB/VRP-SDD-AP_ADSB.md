# VRP-SDD-AP_ADSB — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_ADSB` |
| LLRD | [`VRP-LLRD-AP_ADSB.yaml`](VRP-LLRD-AP_ADSB.yaml) |
| DAL | C |
| Status | planned |

## 1. Purpose

Clean-room BSD design for `VRP_ADSB`, functional parity with ArduPilot `AP_ADSB`.

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
| `VRP_ADSB::init()` | Module initialization |
| `VRP_ADSB::update()` | Periodic update |

## 6. Verification

See SVCP under `test/libraries/VRP_ADSB/` and LLRD test list.
