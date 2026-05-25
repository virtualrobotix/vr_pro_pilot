# VRP-SDD-AP_Scripting — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_Scripting` |
| LLRD | [`VRP-LLRD-AP_Scripting.yaml`](VRP-LLRD-AP_Scripting.yaml) |
| DAL | D |
| Status | planned |

## 1. Purpose

Clean-room BSD design for `VRP_Scripting`, functional parity with ArduPilot `AP_Scripting`.

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
| `VRP_Scripting::init()` | Module initialization |
| `VRP_Scripting::update()` | Periodic update |

## 6. Verification

See SVCP under `test/libraries/VRP_Scripting/` and LLRD test list.
