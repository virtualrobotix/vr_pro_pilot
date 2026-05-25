# VRP-SDD-AP_IOMCU — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_IOMCU` |
| LLRD | [`VRP-LLRD-AP_IOMCU.yaml`](VRP-LLRD-AP_IOMCU.yaml) |
| DAL | C |
| Status | planned |

## 1. Purpose

Clean-room BSD design for `VRP_IOMCU`, functional parity with ArduPilot `AP_IOMCU`.

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
| `VRP_IOMCU::init()` | Module initialization |
| `VRP_IOMCU::update()` | Periodic update |

## 6. Verification

See SVCP under `test/libraries/VRP_IOMCU/` and LLRD test list.
