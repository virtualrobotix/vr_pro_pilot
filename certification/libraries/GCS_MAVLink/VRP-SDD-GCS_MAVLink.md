# VRP-SDD-GCS_MAVLink — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_GCS_MAVLink` |
| LLRD | [`VRP-LLRD-GCS_MAVLink.yaml`](VRP-LLRD-GCS_MAVLink.yaml) |
| DAL | C |
| Status | partial |

## 1. Purpose

Clean-room BSD design for `VRP_GCS_MAVLink`, functional parity with ArduPilot `GCS_MAVLink`.

## 2. Architecture

_TBD during implementation phase 1._

## 3. Data flow

_TBD — uORB topics / HAL interfaces._

## 4. Safety constraints (DAL C)

- Statement coverage 100%
- Requirements-based tests
- Design review

## 5. Interface summary

| API | Description |
|---|---|
| `VRP_GCS_MAVLink::init()` | Module initialization |
| `VRP_GCS_MAVLink::update()` | Periodic update |

## 6. Verification

See SVCP under `test/libraries/VRP_GCS_MAVLink/` and LLRD test list.
