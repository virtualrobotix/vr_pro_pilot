# VRP-SDD-AC_InputManager — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_AC_InputManager` |
| LLRD | [`VRP-LLRD-AC_InputManager.yaml`](VRP-LLRD-AC_InputManager.yaml) |
| DAL | C |
| Status | **wired** |
| Integration | `CopterCore::build_setpoints (Stabilize/Sport)` |
| Phase | 19 |

## 1. Purpose

Clean-room BSD implementation of `VRP_AC_InputManager` with functional parity to ArduPilot `AC_InputManager`.
**Wired** in the multicopter flight loop (see `docs/ARDUCOPTER_PARITY.md`).

## 2. Architecture

RC input scaling and dead-zone for stabilize modes.

## 3. Data flow

RC channels → apply_stabilize → scaled RcChannels → attitude setpoint.

uORB topics: _none (inline struct pass-through)_

## 4. Safety constraints (DAL C)

- Statement coverage 100%
- Requirements-based tests
- Design review

## 5. Interface summary

| API | Description |
|---|---|
| `VRP_AC_InputManager::init()` | Module init |
| `VRP_AC_InputManager::update(rc, armed)` | Process RC state |
| `VRP_AC_InputManager::apply_stabilize(rc, max_tilt_rad)` | Scale roll/pitch/yaw/throttle |

Source: `src/libraries/VRP_AC_InputManager/VRP_AC_InputManager.h`

## 6. Verification

| Test Case | Type |
|---|---|
| `VRP-TST-X01` | SVCP / SITL |
| `VRP-COPTER-T01` | SVCP / SITL |
| `VRP-TC-COPTER-03` | SVCP / SITL |

SVCP: `test/libraries/VRP_AC_InputManager/`
Traceability: `certification/traceability/VRP-RTM-001.md`
