# VRP-SDD-AC_WPNav — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_AC_WPNav` |
| LLRD | [`VRP-LLRD-AC_WPNav.yaml`](VRP-LLRD-AC_WPNav.yaml) |
| DAL | B |
| Status | **wired** |
| Integration | `NavCore (quad path)` |
| Phase | 4 |

## 1. Purpose

Clean-room BSD implementation of `VRP_AC_WPNav` with functional parity to ArduPilot `AC_WPNav`.
**Wired** in the multicopter flight loop (see `docs/ARDUCOPTER_PARITY.md`).

## 2. Architecture

Waypoint navigation: bearing, cross-track error, loiter orbit, RTL home vector, wp-reached detection. Publishes formatted `ACWPNAV` telemetry.

## 3. Data flow

SafetyCore position + mode → VRP_AC_WPNav::update → WpNavOutput → CopterCore/NavCore.

uORB topics: `nav/ac_wp`

## 4. Safety constraints (DAL B)

- MC/DC on safety paths
- No dynamic heap
- Bounded WCET
- MISRA subset

## 5. Interface summary

| API | Description |
|---|---|
| `VRP_AC_WPNav::init(params)` | Load cruise speed, wp radius, loiter radius |
| `VRP_AC_WPNav::update(pos, mode, home)` | Compute nav output for active modes |
| `VRP_AC_WPNav::set_loiter_center(x,y)` | Capture loiter anchor on mode entry |

Source: `src/libraries/VRP_AC_WPNav/VRP_AC_WPNav.h`

## 6. Verification

| Test Case | Type |
|---|---|
| `VRP-TST-N01` | SVCP / SITL |
| `VRP-COPTER-T02` | SVCP / SITL |
| `VRP-TC-COPTER-01` | SVCP / SITL |

SVCP: `test/libraries/VRP_AC_WPNav/`
Traceability: `certification/traceability/VRP-RTM-001.md`
