# VRP-SDD-AP_Arming — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_Arming` |
| LLRD | [`VRP-LLRD-AP_Arming.yaml`](VRP-LLRD-AP_Arming.yaml) |
| DAL | B |
| Status | **wired** |
| Integration | `SafetyCore` |
| Phase | 1 |

## 1. Purpose

Clean-room BSD implementation of `VRP_Arming` with functional parity to ArduPilot `AP_Arming`.
**Wired** in the multicopter flight loop (see `docs/ARDUCOPTER_PARITY.md`).

## 2. Architecture

Pre-arm checks; arm/disarm state machine.

## 3. Data flow

sensor checks → armed flag → ControlCore gate.

uORB topics: `safety/arming`

## 4. Safety constraints (DAL B)

- MC/DC on safety paths
- No dynamic heap
- Bounded WCET
- MISRA subset

## 5. Interface summary

| API | Description |
|---|---|
| `VRP_Arming::init()` | Init |
| `VRP_Arming::update(checks)` | Arming state |

Source: `src/libraries/VRP_Arming/VRP_Arming.h`

## 6. Verification

| Test Case | Type |
|---|---|
| `VRP-TST-S01` | SVCP / SITL |
| `VRP-TC-SAFETY-01` | SVCP / SITL |

SVCP: `test/libraries/VRP_Arming/`
Traceability: `certification/traceability/VRP-RTM-001.md`
