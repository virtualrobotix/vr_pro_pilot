# VRP-SDD-AP_RCMapper — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_RCMapper` |
| LLRD | [`VRP-LLRD-AP_RCMapper.yaml`](VRP-LLRD-AP_RCMapper.yaml) |
| DAL | C |
| Status | planned |

## 1. Purpose

Clean-room BSD design for `VRP_RCMapper`, functional parity with ArduPilot `AP_RCMapper`.

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
| `VRP_RCMapper::init()` | Module initialization |
| `VRP_RCMapper::update()` | Periodic update |

## 6. Verification

See SVCP under `test/libraries/VRP_RCMapper/` and LLRD test list.
