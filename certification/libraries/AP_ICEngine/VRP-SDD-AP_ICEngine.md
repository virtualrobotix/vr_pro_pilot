# VRP-SDD-AP_ICEngine — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_ICEngine` |
| LLRD | [`VRP-LLRD-AP_ICEngine.yaml`](VRP-LLRD-AP_ICEngine.yaml) |
| DAL | C |
| Status | planned |

## 1. Purpose

Clean-room BSD design for `VRP_ICEngine`, functional parity with ArduPilot `AP_ICEngine`.

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
| `VRP_ICEngine::init()` | Module initialization |
| `VRP_ICEngine::update()` | Periodic update |

## 6. Verification

See SVCP under `test/libraries/VRP_ICEngine/` and LLRD test list.
