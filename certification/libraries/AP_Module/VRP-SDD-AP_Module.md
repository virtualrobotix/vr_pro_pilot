# VRP-SDD-AP_Module — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_Module` |
| LLRD | [`VRP-LLRD-AP_Module.yaml`](VRP-LLRD-AP_Module.yaml) |
| DAL | C |
| Status | planned |

## 1. Purpose

Clean-room BSD design for `VRP_Module`, functional parity with ArduPilot `AP_Module`.

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
| `VRP_Module::init()` | Module initialization |
| `VRP_Module::update()` | Periodic update |

## 6. Verification

See SVCP under `test/libraries/VRP_Module/` and LLRD test list.
