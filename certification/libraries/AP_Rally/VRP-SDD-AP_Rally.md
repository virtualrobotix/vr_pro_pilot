# VRP-SDD-AP_Rally — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_Rally` |
| LLRD | [`VRP-LLRD-AP_Rally.yaml`](VRP-LLRD-AP_Rally.yaml) |
| DAL | C |
| Status | **wired** |
| Integration | `SafetyCore RTL fallback` |
| Phase | 12 |

## 1. Purpose

Clean-room BSD implementation of `VRP_Rally` with functional parity to ArduPilot `AP_Rally`.
**Wired** in the multicopter flight loop (see `docs/ARDUCOPTER_PARITY.md`).

## 2. Architecture

Rally point list; SmartRTL → Rally → home nav chain.

## 3. Data flow

RallyStatus → SafetyCore nav_target → CopterCore RTL rally nav.

uORB topics: `safety/rally`

## 4. Safety constraints (DAL C)

- Statement coverage 100%
- Requirements-based tests
- Design review

## 5. Interface summary

| API | Description |
|---|---|
| `VRP_Rally::init()` | Init default rally |
| `VRP_Rally::target_at(index)` | Rally point coordinates |
| `VRP_Rally::nearest_index(x,y)` | Nearest rally index |

Source: `src/libraries/VRP_Rally/VRP_Rally.h`

## 6. Verification

| Test Case | Type |
|---|---|
| `VRP-TST-L02` | SVCP / SITL |
| `VRP-COPTER-T04` | SVCP / SITL |
| `VRP-TC-COPTER-15` | SVCP / SITL |

SVCP: `test/libraries/VRP_Rally/`
Traceability: `certification/traceability/VRP-RTM-001.md`
