# VRP-SDD-AP_Follow — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_Follow` |
| LLRD | [`VRP-LLRD-AP_Follow.yaml`](VRP-LLRD-AP_Follow.yaml) |
| DAL | C |
| Status | **wired** |
| Integration | `CopterCore Guided + LibraryCore` |
| Phase | 15 |

## 1. Purpose

Clean-room BSD implementation of `VRP_Follow` with functional parity to ArduPilot `AP_Follow`.
**Wired** in the multicopter flight loop (see `docs/ARDUCOPTER_PARITY.md`).

## 2. Architecture

Bearing to follow target; active in Loiter/Auto/Guided.

## 3. Data flow

target XY + pos → FollowState → Guided lean override.

uORB topics: _none (inline struct pass-through)_

## 4. Safety constraints (DAL C)

- Statement coverage 100%
- Requirements-based tests
- Design review

## 5. Interface summary

| API | Description |
|---|---|
| `VRP_Follow::init()` | Init |
| `VRP_Follow::update(mode, tx, ty, x, y)` | Follow bearing |

Source: `src/libraries/VRP_Follow/VRP_Follow.h`

## 6. Verification

| Test Case | Type |
|---|---|
| `VRP-TST-O02` | SVCP / SITL |
| `VRP-COPTER-T04` | SVCP / SITL |
| `VRP-TC-COPTER-14` | SVCP / SITL |

SVCP: `test/libraries/VRP_Follow/`
Traceability: `certification/traceability/VRP-RTM-001.md`
