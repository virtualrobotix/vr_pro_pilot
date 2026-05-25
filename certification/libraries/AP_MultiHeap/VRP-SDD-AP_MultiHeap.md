# VRP-SDD-AP_MultiHeap — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_MultiHeap` |
| LLRD | [`VRP-LLRD-AP_MultiHeap.yaml`](VRP-LLRD-AP_MultiHeap.yaml) |
| DAL | C |
| Status | planned |

## 1. Purpose

Clean-room BSD design for `VRP_MultiHeap`, functional parity with ArduPilot `AP_MultiHeap`.

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
| `VRP_MultiHeap::init()` | Module initialization |
| `VRP_MultiHeap::update()` | Periodic update |

## 6. Verification

See SVCP under `test/libraries/VRP_MultiHeap/` and LLRD test list.
