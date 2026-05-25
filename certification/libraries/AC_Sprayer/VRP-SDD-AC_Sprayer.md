# VRP-SDD-AC_Sprayer — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_AC_Sprayer` |
| LLRD | [`VRP-LLRD-AC_Sprayer.yaml`](VRP-LLRD-AC_Sprayer.yaml) |
| DAL | C |
| Status | **wired** |
| Integration | `CopterCore Auto mode` |
| Phase | 19 |

## 1. Purpose

Clean-room BSD implementation of `VRP_AC_Sprayer` with functional parity to ArduPilot `AC_Sprayer`.
**Wired** in the multicopter flight loop (see `docs/ARDUCOPTER_PARITY.md`).

## 2. Architecture

Sprayer pump state from aux2 in Auto mode.

## 3. Data flow

mode Auto + aux2 → SprayerState → telemetry.

uORB topics: _none (inline struct pass-through)_

## 4. Safety constraints (DAL C)

- Statement coverage 100%
- Requirements-based tests
- Design review

## 5. Interface summary

| API | Description |
|---|---|
| `VRP_AC_Sprayer::init()` | Init |
| `VRP_AC_Sprayer::update(auto, aux2)` | Sprayer on/off state |

Source: `src/libraries/VRP_AC_Sprayer/VRP_AC_Sprayer.h`

## 6. Verification

| Test Case | Type |
|---|---|
| `VRP-TST-X02` | SVCP / SITL |
| `VRP-COPTER-T03` | SVCP / SITL |
| `VRP-TC-COPTER-09` | SVCP / SITL |

SVCP: `test/libraries/VRP_AC_Sprayer/`
Traceability: `certification/traceability/VRP-RTM-001.md`
