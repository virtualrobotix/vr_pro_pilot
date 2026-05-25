# VRP-SDD-AP_SmartRTL — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_SmartRTL` |
| LLRD | [`VRP-LLRD-AP_SmartRTL.yaml`](VRP-LLRD-AP_SmartRTL.yaml) |
| DAL | B |
| Status | **wired** |
| Integration | `SafetyCore nav_target` |
| Phase | 7 |

## 1. Purpose

Clean-room BSD implementation of `VRP_SmartRTL` with functional parity to ArduPilot `AP_SmartRTL`.
**Wired** in the multicopter flight loop (see `docs/ARDUCOPTER_PARITY.md`).

## 2. Architecture

Breadcrumb RTL path; preferred over direct home when active.

## 3. Data flow

position history → SmartRTL target → SafetyCore RTL nav.

uORB topics: `safety/smartrtl`

## 4. Safety constraints (DAL B)

- MC/DC on safety paths
- No dynamic heap
- Bounded WCET
- MISRA subset

## 5. Interface summary

| API | Description |
|---|---|
| `VRP_SmartRTL::init()` | Init |
| `VRP_SmartRTL::update(pos, rtl_active)` | Breadcrumb target |

Source: `src/libraries/VRP_SmartRTL/VRP_SmartRTL.h`

## 6. Verification

| Test Case | Type |
|---|---|
| `VRP-TST-F01` | SVCP / SITL |
| `VRP-TC-COPTER-19` | SVCP / SITL |

SVCP: `test/libraries/VRP_SmartRTL/`
Traceability: `certification/traceability/VRP-RTM-001.md`
