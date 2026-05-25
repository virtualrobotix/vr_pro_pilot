# VRP-SDD-AC_AttitudeControl — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_AC_AttitudeControl` |
| LLRD | [`VRP-LLRD-AC_AttitudeControl.yaml`](VRP-LLRD-AC_AttitudeControl.yaml) |
| DAL | B |
| Status | **wired** |
| Integration | `ControlCore::update_quad` |
| Phase | 1 |

## 1. Purpose

Clean-room BSD implementation of `VRP_AC_AttitudeControl` with functional parity to ArduPilot `AC_AttitudeControl`.
**Wired** in the multicopter flight loop (see `docs/ARDUCOPTER_PARITY.md`).

## 2. Architecture

PID cascaded attitude controller with optional position-hold overlay. Roll/pitch/yaw rate PIDs produce `ControlTorque`; `update_pos` maps WPNav output and altitude error into lean angles and thrust base.

## 3. Data flow

NavCore/SafetyCore → VehicleSetpoints → ControlCore → VRP_AC_AttitudeControl::update / update_pos → VRP_Motors::mix_quad.

uORB topics: `control/attitude`, `control/pos`

## 4. Safety constraints (DAL B)

- MC/DC on safety paths
- No dynamic heap
- Bounded WCET
- MISRA subset

## 5. Interface summary

| API | Description |
|---|---|
| `VRP_AC_AttitudeControl::init(max_tilt_deg)` | Initialize PID limits and max lean angle |
| `VRP_AC_AttitudeControl::apply_autotune_scale(scale)` | Scale attitude PID gains from AutoTune aux |
| `VRP_AC_AttitudeControl::update(attitude, sp, dt_s)` | Compute roll/pitch/yaw torque |
| `VRP_AC_AttitudeControl::update_pos(pos, nav, target_z, max_tilt, alt_hold)` | Pos-hold setpoint (POSCTL) |

Source: `src/libraries/VRP_AC_AttitudeControl/VRP_AC_AttitudeControl.h`

## 6. Verification

| Test Case | Type |
|---|---|
| `VRP-TST-C01` | SVCP / SITL |
| `VRP-COPTER-T02` | SVCP / SITL |
| `VRP-TC-COPTER-02` | SVCP / SITL |

SVCP: `test/libraries/VRP_AC_AttitudeControl/`
Traceability: `certification/traceability/VRP-RTM-001.md`
