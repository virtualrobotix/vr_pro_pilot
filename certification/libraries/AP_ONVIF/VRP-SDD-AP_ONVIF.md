# VRP-SDD-AP_ONVIF — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_ONVIF` |
| LLRD | [`VRP-LLRD-AP_ONVIF.yaml`](VRP-LLRD-AP_ONVIF.yaml) |
| DAL | E |
| Status | planned |

## 1. Purpose

Clean-room BSD design for `VRP_ONVIF`, functional parity with ArduPilot `AP_ONVIF`.

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
| `VRP_ONVIF::init()` | Module initialization |
| `VRP_ONVIF::update()` | Periodic update |

## 6. Verification

See SVCP under `test/libraries/VRP_ONVIF/` and LLRD test list.
