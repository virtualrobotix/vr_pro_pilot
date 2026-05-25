# VRP-SDD-AP_Frsky_Telem — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_Frsky_Telem` |
| LLRD | [`VRP-LLRD-AP_Frsky_Telem.yaml`](VRP-LLRD-AP_Frsky_Telem.yaml) |
| DAL | E |
| Status | planned |

## 1. Purpose

Clean-room BSD design for `VRP_Frsky_Telem`, functional parity with ArduPilot `AP_Frsky_Telem`.

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
| `VRP_Frsky_Telem::init()` | Module initialization |
| `VRP_Frsky_Telem::update()` | Periodic update |

## 6. Verification

See SVCP under `test/libraries/VRP_Frsky_Telem/` and LLRD test list.
