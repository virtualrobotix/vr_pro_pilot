# VRP-SDD-AP_Devo_Telem — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_Devo_Telem` |
| LLRD | [`VRP-LLRD-AP_Devo_Telem.yaml`](VRP-LLRD-AP_Devo_Telem.yaml) |
| DAL | E |
| Status | planned |

## 1. Purpose

Clean-room BSD design for `VRP_Devo_Telem`, functional parity with ArduPilot `AP_Devo_Telem`.

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
| `VRP_Devo_Telem::init()` | Module initialization |
| `VRP_Devo_Telem::update()` | Periodic update |

## 6. Verification

See SVCP under `test/libraries/VRP_Devo_Telem/` and LLRD test list.
