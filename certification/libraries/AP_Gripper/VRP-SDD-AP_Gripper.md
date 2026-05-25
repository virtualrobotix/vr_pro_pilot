# VRP-SDD-AP_Gripper — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_Gripper` |
| LLRD | [`VRP-LLRD-AP_Gripper.yaml`](VRP-LLRD-AP_Gripper.yaml) |
| DAL | C |
| Status | planned |

## 1. Purpose

Clean-room BSD design for `VRP_Gripper`, functional parity with ArduPilot `AP_Gripper`.

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
| `VRP_Gripper::init()` | Module initialization |
| `VRP_Gripper::update()` | Periodic update |

## 6. Verification

See SVCP under `test/libraries/VRP_Gripper/` and LLRD test list.
