# VRP-SDD-AP_RCTelemetry — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_RCTelemetry` |
| LLRD | [`VRP-LLRD-AP_RCTelemetry.yaml`](VRP-LLRD-AP_RCTelemetry.yaml) |
| DAL | E |
| Status | planned |

## 1. Purpose

Clean-room BSD design for `VRP_RCTelemetry`, functional parity with ArduPilot `AP_RCTelemetry`.

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
| `VRP_RCTelemetry::init()` | Module initialization |
| `VRP_RCTelemetry::update()` | Periodic update |

## 6. Verification

See SVCP under `test/libraries/VRP_RCTelemetry/` and LLRD test list.
