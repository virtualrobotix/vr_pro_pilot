# VRP-SDD-AC_PrecLand — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_AC_PrecLand` |
| LLRD | [`VRP-LLRD-AC_PrecLand.yaml`](VRP-LLRD-AC_PrecLand.yaml) |
| DAL | B |
| Status | **wired** |
| Integration | `CopterCore Land mode` |
| Phase | 17 |

## 1. Purpose

Clean-room BSD implementation of `VRP_AC_PrecLand` with functional parity to ArduPilot `AC_PrecLand`.
**Wired** in the multicopter flight loop (see `docs/ARDUCOPTER_PARITY.md`).

## 2. Architecture

Range-finder aided precision landing; reduces lean when target valid.

## 3. Data flow

RangeFinder + Land mode → PrecLandState → attitude damping in CopterCore.

uORB topics: _none (inline struct pass-through)_

## 4. Safety constraints (DAL B)

- MC/DC on safety paths
- No dynamic heap
- Bounded WCET
- MISRA subset

## 5. Interface summary

| API | Description |
|---|---|
| `VRP_AC_PrecLand::init()` | Init |
| `VRP_AC_PrecLand::update(rng, armed, mode)` | Update precision land state |

Source: `src/libraries/VRP_AC_PrecLand/VRP_AC_PrecLand.h`

## 6. Verification

| Test Case | Type |
|---|---|
| `VRP-TST-T01` | SVCP / SITL |
| `VRP-COPTER-T03` | SVCP / SITL |
| `VRP-TC-COPTER-05` | SVCP / SITL |

SVCP: `test/libraries/VRP_AC_PrecLand/`
Traceability: `certification/traceability/VRP-RTM-001.md`
