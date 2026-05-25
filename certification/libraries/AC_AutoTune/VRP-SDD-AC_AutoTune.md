# VRP-SDD-AC_AutoTune — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_AC_AutoTune` |
| LLRD | [`VRP-LLRD-AC_AutoTune.yaml`](VRP-LLRD-AC_AutoTune.yaml) |
| DAL | C |
| Status | **wired** |
| Integration | `CopterCore → ControlCore autotune_scale` |
| Phase | 17 |

## 1. Purpose

Clean-room BSD implementation of `VRP_AC_AutoTune` with functional parity to ArduPilot `AC_AutoTune`.
**Wired** in the multicopter flight loop (see `docs/ARDUCOPTER_PARITY.md`).

## 2. Architecture

Aux1-driven PID scale factor for in-flight tuning.

## 3. Data flow

RC aux1 → AutoTuneState → autotune_scale → AttitudeControl PID scale.

uORB topics: _none (inline struct pass-through)_

## 4. Safety constraints (DAL C)

- Statement coverage 100%
- Requirements-based tests
- Design review

## 5. Interface summary

| API | Description |
|---|---|
| `VRP_AC_AutoTune::init()` | Init |
| `VRP_AC_AutoTune::update(armed, aux1, dt_ms)` | Update tune percentage |

Source: `src/libraries/VRP_AC_AutoTune/VRP_AC_AutoTune.h`

## 6. Verification

| Test Case | Type |
|---|---|
| `VRP-TST-T01` | SVCP / SITL |
| `VRP-COPTER-T03` | SVCP / SITL |
| `VRP-TC-COPTER-06` | SVCP / SITL |

SVCP: `test/libraries/VRP_AC_AutoTune/`
Traceability: `certification/traceability/VRP-RTM-001.md`
