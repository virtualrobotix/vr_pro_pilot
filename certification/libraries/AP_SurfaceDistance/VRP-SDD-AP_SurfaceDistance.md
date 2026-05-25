# VRP-SDD-AP_SurfaceDistance — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_SurfaceDistance` |
| LLRD | [`VRP-LLRD-AP_SurfaceDistance.yaml`](VRP-LLRD-AP_SurfaceDistance.yaml) |
| DAL | C |
| Status | **wired** |
| Integration | `CopterCore AGL hold` |
| Phase | 12 |

## 1. Purpose

Clean-room BSD implementation of `VRP_SurfaceDistance` with functional parity to ArduPilot `AP_SurfaceDistance`.
**Wired** in the multicopter flight loop (see `docs/ARDUCOPTER_PARITY.md`).

## 2. Architecture

AGL from rangefinder + pitch compensation; alt adjustment in nav.

## 3. Data flow

RangeFinder → SurfaceDistanceSample → thrust/alt bias in nav attitude.

uORB topics: _none (inline struct pass-through)_

## 4. Safety constraints (DAL C)

- Statement coverage 100%
- Requirements-based tests
- Design review

## 5. Interface summary

| API | Description |
|---|---|
| `VRP_SurfaceDistance::init()` | Init |
| `VRP_SurfaceDistance::update(rng, pitch_rad)` | AGL sample |

Source: `src/libraries/VRP_SurfaceDistance/VRP_SurfaceDistance.h`

## 6. Verification

| Test Case | Type |
|---|---|
| `VRP-TST-L01` | SVCP / SITL |
| `VRP-COPTER-T01` | SVCP / SITL |
| `VRP-TC-COPTER-13` | SVCP / SITL |

SVCP: `test/libraries/VRP_SurfaceDistance/`
Traceability: `certification/traceability/VRP-RTM-001.md`
