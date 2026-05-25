# VRP-SDD-AP_InertialNav — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_InertialNav` |
| LLRD | [`VRP-LLRD-AP_InertialNav.yaml`](VRP-LLRD-AP_InertialNav.yaml) |
| DAL | B |
| Status | **wired** |
| Integration | `CopterCore nav damping` |
| Phase | 18 |

## 1. Purpose

Clean-room BSD implementation of `VRP_InertialNav` with functional parity to ArduPilot `AP_InertialNav`.
**Wired** in the multicopter flight loop (see `docs/ARDUCOPTER_PARITY.md`).

## 2. Architecture

Velocity estimate from local position delta; damping on nav attitude.

## 3. Data flow

LocalPosition → InertialNavState → apply_nav_attitude velocity damping.

uORB topics: _none (inline struct pass-through)_

## 4. Safety constraints (DAL B)

- MC/DC on safety paths
- No dynamic heap
- Bounded WCET
- MISRA subset

## 5. Interface summary

| API | Description |
|---|---|
| `VRP_InertialNav::init()` | Init |
| `VRP_InertialNav::update(pos, active)` | Velocity state |

Source: `src/libraries/VRP_InertialNav/VRP_InertialNav.h`

## 6. Verification

| Test Case | Type |
|---|---|
| `VRP-TST-W01` | SVCP / SITL |
| `VRP-COPTER-T01` | SVCP / SITL |
| `VRP-TC-COPTER-12` | SVCP / SITL |

SVCP: `test/libraries/VRP_InertialNav/`
Traceability: `certification/traceability/VRP-RTM-001.md`
