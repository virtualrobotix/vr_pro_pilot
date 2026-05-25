# VRP-SDD-AP_BoardConfig — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_BoardConfig` |
| LLRD | [`VRP-LLRD-AP_BoardConfig.yaml`](VRP-LLRD-AP_BoardConfig.yaml) |
| DAL | C |
| Status | planned |

## 1. Purpose

Clean-room BSD design for `VRP_BoardConfig`, functional parity with ArduPilot `AP_BoardConfig`.

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
| `VRP_BoardConfig::init()` | Module initialization |
| `VRP_BoardConfig::update()` | Periodic update |

## 6. Verification

See SVCP under `test/libraries/VRP_BoardConfig/` and LLRD test list.
