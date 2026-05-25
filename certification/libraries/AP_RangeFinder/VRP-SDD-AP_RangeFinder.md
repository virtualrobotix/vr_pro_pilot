# VRP-SDD-AP_RangeFinder — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_RangeFinder` |
| LLRD | [`VRP-LLRD-AP_RangeFinder.yaml`](VRP-LLRD-AP_RangeFinder.yaml) |
| DAL | C |
| Status | **wired** |
| Integration | `SafetyCore sensors → Landing/PrecLand/Surface` |
| Phase | 8 |

## 1. Purpose

Clean-room BSD implementation of `VRP_RangeFinder` with functional parity to ArduPilot `AP_RangeFinder`.
**Wired** in the multicopter flight loop (see `docs/ARDUCOPTER_PARITY.md`).

## 2. Architecture

Rangefinder sample for AGL and precision land.

## 3. Data flow

HAL/sim → RangeFinderSample → Landing, PrecLand, SurfaceDistance.

uORB topics: `sensors/rng`

## 4. Safety constraints (DAL C)

- Statement coverage 100%
- Requirements-based tests
- Design review

## 5. Interface summary

| API | Description |
|---|---|
| `VRP_RangeFinder::init()` | Init |
| `VRP_RangeFinder::update(sim_rng)` | Range sample |

Source: `src/libraries/VRP_RangeFinder/VRP_RangeFinder.h`

## 6. Verification

| Test Case | Type |
|---|---|
| `VRP-TST-H01` | SVCP / SITL |
| `VRP-TC-COPTER-18` | SVCP / SITL |

SVCP: `test/libraries/VRP_RangeFinder/`
Traceability: `certification/traceability/VRP-RTM-001.md`
