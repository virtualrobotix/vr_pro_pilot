# VRP-SDD-AP_Button — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_Button` |
| LLRD | [`VRP-LLRD-AP_Button.yaml`](VRP-LLRD-AP_Button.yaml) |
| DAL | D |
| Status | planned |

## 1. Purpose

Clean-room BSD design for `VRP_Button`, functional parity with ArduPilot `AP_Button`.

## 2. Architecture

_TBD during implementation phase 3._

## 3. Data flow

_TBD — uORB topics / HAL interfaces._

## 4. Safety constraints (DAL D)

- Unit tests for public API
- Requirements traceability

## 5. Interface summary

| API | Description |
|---|---|
| `VRP_Button::init()` | Module initialization |
| `VRP_Button::update()` | Periodic update |

## 6. Verification

See SVCP under `test/libraries/VRP_Button/` and LLRD test list.
