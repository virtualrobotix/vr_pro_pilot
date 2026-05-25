# VRP-SDD-AP_LeakDetector — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_LeakDetector` |
| LLRD | [`VRP-LLRD-AP_LeakDetector.yaml`](VRP-LLRD-AP_LeakDetector.yaml) |
| DAL | C |
| Status | planned |

## 1. Purpose

Clean-room BSD design for `VRP_LeakDetector`, functional parity with ArduPilot `AP_LeakDetector`.

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
| `VRP_LeakDetector::init()` | Module initialization |
| `VRP_LeakDetector::update()` | Periodic update |

## 6. Verification

See SVCP under `test/libraries/VRP_LeakDetector/` and LLRD test list.
