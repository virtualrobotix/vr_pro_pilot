# VRP-SDD-AP_EFI — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_EFI` |
| LLRD | [`VRP-LLRD-AP_EFI.yaml`](VRP-LLRD-AP_EFI.yaml) |
| DAL | C |
| Status | planned |

## 1. Purpose

Clean-room BSD design for `VRP_EFI`, functional parity with ArduPilot `AP_EFI`.

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
| `VRP_EFI::init()` | Module initialization |
| `VRP_EFI::update()` | Periodic update |

## 6. Verification

See SVCP under `test/libraries/VRP_EFI/` and LLRD test list.
