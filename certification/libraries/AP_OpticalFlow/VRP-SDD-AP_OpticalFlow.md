# VRP-SDD-AP_OpticalFlow — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_OpticalFlow` |
| LLRD | [`VRP-LLRD-AP_OpticalFlow.yaml`](VRP-LLRD-AP_OpticalFlow.yaml) |
| DAL | C |
| Status | **wired** |
| Integration | `CopterCore flow loiter` |
| Phase | 11 |

## 1. Purpose

Clean-room BSD implementation of `VRP_OpticalFlow` with functional parity to ArduPilot `AP_OpticalFlow`.
**Wired** in the multicopter flight loop (see `docs/ARDUCOPTER_PARITY.md`).

## 2. Architecture

Optical flow sample → roll/pitch damping for indoor loiter.

## 3. Data flow

OpticalFlowSample → apply_flow_loiter in nav modes.

uORB topics: _none (inline struct pass-through)_

## 4. Safety constraints (DAL C)

- Statement coverage 100%
- Requirements-based tests
- Design review

## 5. Interface summary

| API | Description |
|---|---|
| `VRP_OpticalFlow::init()` | Init |
| `VRP_OpticalFlow::update(flow, quality_min)` | Flow sample processing |

Source: `src/libraries/VRP_OpticalFlow/VRP_OpticalFlow.h`

## 6. Verification

| Test Case | Type |
|---|---|
| `VRP-TST-K01` | SVCP / SITL |
| `VRP-TC-COPTER-16` | SVCP / SITL |

SVCP: `test/libraries/VRP_OpticalFlow/`
Traceability: `certification/traceability/VRP-RTM-001.md`
