# VRP-SDD-AP_Motors — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_Motors` |
| LLRD | [`VRP-LLRD-AP_Motors.yaml`](VRP-LLRD-AP_Motors.yaml) |
| DAL | B |
| Status | **wired** |
| Integration | `ControlCore::mix_quad` |
| Phase | 1 |

## 1. Purpose

Clean-room BSD implementation of `VRP_Motors` with functional parity to ArduPilot `AP_Motors`.
**Wired** in the multicopter flight loop (see `docs/ARDUCOPTER_PARITY.md`).

## 2. Architecture

Quad X mix with spool, yaw headroom, tilt limiting.

## 3. Data flow

thrust + ControlTorque → MotorOutputQuad m1..m4.

uORB topics: `actuators/quad`

## 4. Safety constraints (DAL B)

- MC/DC on safety paths
- No dynamic heap
- Bounded WCET
- MISRA subset

## 5. Interface summary

| API | Description |
|---|---|
| `VRP_Motors::init(max_tilt_deg)` | Init mix limits |
| `VRP_Motors::mix_quad(thrust, torque, spool, yaw_headroom)` | Motor mixing |

Source: `src/modules/control_allocator/ControlAllocator.h`

## 6. Verification

| Test Case | Type |
|---|---|
| `VRP-TST-C01` | SVCP / SITL |
| `VRP-COPTER-T01` | SVCP / SITL |
| `VRP-TC-COPTER-17` | SVCP / SITL |

SVCP: `test/libraries/VRP_Motors/`
Traceability: `certification/traceability/VRP-RTM-001.md`
