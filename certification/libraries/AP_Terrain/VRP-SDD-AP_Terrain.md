# VRP-SDD-AP_Terrain — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_Terrain` |
| LLRD | [`VRP-LLRD-AP_Terrain.yaml`](VRP-LLRD-AP_Terrain.yaml) |
| DAL | C |
| Status | planned |

## 1. Purpose

Clean-room BSD design for `VRP_Terrain`, functional parity with ArduPilot `AP_Terrain`.

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
| `VRP_Terrain::init()` | Module initialization |
| `VRP_Terrain::update()` | Periodic update |

## 6. Verification

See SVCP under `test/libraries/VRP_Terrain/` and LLRD test list.
