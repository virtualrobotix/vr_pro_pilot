# VRP-SDD-AC_PID — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_AC_PID` |
| LLRD | [`VRP-LLRD-AC_PID.yaml`](VRP-LLRD-AC_PID.yaml) |
| DAL | C |
| Status | **wired** |
| Integration | `CopterCore cross-track correction` |
| Phase | 19 |

## 1. Purpose

Clean-room BSD implementation of `VRP_AC_PID` with functional parity to ArduPilot `AC_PID`.
**Wired** in the multicopter flight loop (see `docs/ARDUCOPTER_PARITY.md`).

## 2. Architecture

PID on cross-track error; output biases roll setpoint.

## 3. Data flow

WpNav cross_track_m → VRP_AC_PID → roll correction in CopterCore.

uORB topics: _none (inline struct pass-through)_

## 4. Safety constraints (DAL C)

- Statement coverage 100%
- Requirements-based tests
- Design review

## 5. Interface summary

| API | Description |
|---|---|
| `VRP_AC_PID::init()` | Init |
| `VRP_AC_PID::update(active, error)` | PID step with output |

Source: `src/libraries/VRP_AC_PID/VRP_AC_PID.h`

## 6. Verification

| Test Case | Type |
|---|---|
| `VRP-TST-X01` | SVCP / SITL |
| `VRP-COPTER-T03` | SVCP / SITL |
| `VRP-TC-COPTER-08` | SVCP / SITL |

SVCP: `test/libraries/VRP_AC_PID/`
Traceability: `certification/traceability/VRP-RTM-001.md`
