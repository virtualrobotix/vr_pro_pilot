# VRP-SDD-AC_CustomControl — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_AC_CustomControl` |
| LLRD | [`VRP-LLRD-AC_CustomControl.yaml`](VRP-LLRD-AC_CustomControl.yaml) |
| DAL | C |
| Status | **wired** |
| Integration | `CopterCore overlay` |
| Phase | 19 |

## 1. Purpose

Clean-room BSD implementation of `VRP_AC_CustomControl` with functional parity to ArduPilot `AC_CustomControl`.
**Wired** in the multicopter flight loop (see `docs/ARDUCOPTER_PARITY.md`).

## 2. Architecture

Custom roll/pitch overlay on attitude setpoint.

## 3. Data flow

RC + mode → CustomControlState → apply_custom_overlay.

uORB topics: _none (inline struct pass-through)_

## 4. Safety constraints (DAL C)

- Statement coverage 100%
- Requirements-based tests
- Design review

## 5. Interface summary

| API | Description |
|---|---|
| `VRP_AC_CustomControl::init()` | Init |
| `VRP_AC_CustomControl::update(armed, roll, pitch)` | Custom overlay state |

Source: `src/libraries/VRP_AC_CustomControl/VRP_AC_CustomControl.h`

## 6. Verification

| Test Case | Type |
|---|---|
| `VRP-TST-X01` | SVCP / SITL |
| `VRP-COPTER-T03` | SVCP / SITL |
| `VRP-TC-COPTER-07` | SVCP / SITL |

SVCP: `test/libraries/VRP_AC_CustomControl/`
Traceability: `certification/traceability/VRP-RTM-001.md`
