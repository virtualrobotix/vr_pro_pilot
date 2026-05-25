# VRP-SDD-AP_Landing — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_Landing` |
| LLRD | [`VRP-LLRD-AP_Landing.yaml`](VRP-LLRD-AP_Landing.yaml) |
| DAL | B |
| Status | **wired** |
| Integration | `CopterCore Land mode` |
| Phase | 8 |

## 1. Purpose

Clean-room BSD implementation of `VRP_Landing` with functional parity to ArduPilot `AP_Landing`.
**Wired** in the multicopter flight loop (see `docs/ARDUCOPTER_PARITY.md`).

## 2. Architecture

Multi-phase land: approach, flare, touch-down; throttle from altitude error.

## 3. Data flow

pos + rangefinder → LandingSetpoint → CopterCore thrust in Land.

uORB topics: _none (inline struct pass-through)_

## 4. Safety constraints (DAL B)

- MC/DC on safety paths
- No dynamic heap
- Bounded WCET
- MISRA subset

## 5. Interface summary

| API | Description |
|---|---|
| `VRP_Landing::init(flare_alt, land_alt)` | Init land parameters |
| `VRP_Landing::update(pos, rng, dt_s)` | Land phase machine |
| `VRP_Landing::reset()` | Reset land state |

Source: `src/libraries/VRP_Landing/VRP_Landing.h`

## 6. Verification

| Test Case | Type |
|---|---|
| `VRP-TST-H02` | SVCP / SITL |
| `VRP-COPTER-T05` | SVCP / SITL |
| `VRP-TC-COPTER-11` | SVCP / SITL |

SVCP: `test/libraries/VRP_Landing/`
Traceability: `certification/traceability/VRP-RTM-001.md`
