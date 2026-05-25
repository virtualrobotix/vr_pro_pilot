# VRP-SDD-AP_Menu — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_Menu` |
| LLRD | [`VRP-LLRD-AP_Menu.yaml`](VRP-LLRD-AP_Menu.yaml) |
| DAL | D |
| Status | planned |

## 1. Purpose

Clean-room BSD design for `VRP_Menu`, functional parity with ArduPilot `AP_Menu`.

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
| `VRP_Menu::init()` | Module initialization |
| `VRP_Menu::update()` | Periodic update |

## 6. Verification

See SVCP under `test/libraries/VRP_Menu/` and LLRD test list.
