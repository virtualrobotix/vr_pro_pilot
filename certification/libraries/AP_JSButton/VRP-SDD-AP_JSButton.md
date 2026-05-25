# VRP-SDD-AP_JSButton — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_JSButton` |
| LLRD | [`VRP-LLRD-AP_JSButton.yaml`](VRP-LLRD-AP_JSButton.yaml) |
| DAL | C |
| Status | planned |

## 1. Purpose

Clean-room BSD design for `VRP_JSButton`, functional parity with ArduPilot `AP_JSButton`.

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
| `VRP_JSButton::init()` | Module initialization |
| `VRP_JSButton::update()` | Periodic update |

## 6. Verification

See SVCP under `test/libraries/VRP_JSButton/` and LLRD test list.
