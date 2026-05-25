# VRP-SDD-AC_Avoidance — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_AC_Avoidance` |
| LLRD | [`VRP-LLRD-AC_Avoidance.yaml`](VRP-LLRD-AC_Avoidance.yaml) |
| DAL | C |
| Status | **wired** |
| Integration | `SafetyCore::avoidance → CopterCore overlay` |
| Phase | 10 |

## 1. Purpose

Clean-room BSD implementation of `VRP_AC_Avoidance` with functional parity to ArduPilot `AC_Avoidance`.
**Wired** in the multicopter flight loop (see `docs/ARDUCOPTER_PARITY.md`).

## 2. Architecture

Bearing/speed avoidance vector from ADSB/proximity; applied as roll/pitch bias.

## 3. Data flow

ADSB sample → VRP_AC_Avoidance → AvoidanceOutput → CopterCore::apply_avoidance.

uORB topics: `safety/avoidance`

## 4. Safety constraints (DAL C)

- Statement coverage 100%
- Requirements-based tests
- Design review

## 5. Interface summary

| API | Description |
|---|---|
| `VRP_AC_Avoidance::init()` | Init |
| `VRP_AC_Avoidance::update(adsb, proximity, armed)` | Compute avoidance output |

Source: `src/libraries/VRP_AC_Avoidance/VRP_AC_Avoidance.h`

## 6. Verification

| Test Case | Type |
|---|---|
| `VRP-TST-J01` | SVCP / SITL |
| `VRP-COPTER-T04` | SVCP / SITL |
| `VRP-TC-COPTER-04` | SVCP / SITL |

SVCP: `test/libraries/VRP_AC_Avoidance/`
Traceability: `certification/traceability/VRP-RTM-001.md`
