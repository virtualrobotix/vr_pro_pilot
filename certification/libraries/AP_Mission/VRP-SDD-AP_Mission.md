# VRP-SDD-AP_Mission — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_Mission` |
| LLRD | [`VRP-LLRD-AP_Mission.yaml`](VRP-LLRD-AP_Mission.yaml) |
| DAL | B |
| Status | **wired** |
| Integration | `SafetyCore mission engine` |
| Phase | 1 |

## 1. Purpose

Clean-room BSD implementation of `VRP_Mission` with functional parity to ArduPilot `AP_Mission`.
**Wired** in the multicopter flight loop (see `docs/ARDUCOPTER_PARITY.md`).

## 2. Architecture

Mission item sequencer; WP commands for Auto mode.

## 3. Data flow

mission items → active WP → NavCore target.

uORB topics: `nav/mission`

## 4. Safety constraints (DAL B)

- MC/DC on safety paths
- No dynamic heap
- Bounded WCET
- MISRA subset

## 5. Interface summary

| API | Description |
|---|---|
| `VRP_Mission::init()` | Init |
| `VRP_Mission::advance(pos)` | Mission progression |

Source: `src/libraries/VRP_Mission/VRP_Mission.h`

## 6. Verification

| Test Case | Type |
|---|---|
| `VRP-TST-B01` | SVCP / SITL |
| `VRP-TST-N01` | SVCP / SITL |
| `VRP-TC-MISSION-01` | SVCP / SITL |

SVCP: `test/libraries/VRP_Mission/`
Traceability: `certification/traceability/VRP-RTM-001.md`
