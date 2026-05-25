# VRP-SDD-AC_Fence — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_AC_Fence` |
| LLRD | [`VRP-LLRD-AC_Fence.yaml`](VRP-LLRD-AC_Fence.yaml) |
| DAL | B |
| Status | **wired** |
| Integration | `SafetyCore fence breach` |
| Phase | 1 |

## 1. Purpose

Clean-room BSD implementation of `VRP_AC_Fence` with functional parity to ArduPilot `AC_Fence`.
**Wired** in the multicopter flight loop (see `docs/ARDUCOPTER_PARITY.md`).

## 2. Architecture

Geofence cylinder; breach triggers RTL/disarm path.

## 3. Data flow

LocalPosition → VRP_AC_Fence → fence_breached → SafetyCore RTL.

uORB topics: `safety/fence`

## 4. Safety constraints (DAL B)

- MC/DC on safety paths
- No dynamic heap
- Bounded WCET
- MISRA subset

## 5. Interface summary

| API | Description |
|---|---|
| `VRP_AC_Fence::init(radius_m)` | Init |
| `VRP_AC_Fence::update(pos, armed)` | Fence check |

Source: `src/libraries/VRP_AC_Fence/VRP_AC_Fence.h`

## 6. Verification

| Test Case | Type |
|---|---|
| `VRP-TST-C03` | SVCP / SITL |
| `VRP-TC-COPTER-10` | SVCP / SITL |

SVCP: `test/libraries/VRP_AC_Fence/`
Traceability: `certification/traceability/VRP-RTM-001.md`
