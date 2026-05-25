# VRP-SDD-AR_WPNav — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_AR_WPNav` |
| LLRD | [`VRP-LLRD-AR_WPNav.yaml`](VRP-LLRD-AR_WPNav.yaml) |
| DAL | B |
| Status | partial |
| Phase | 18 |

## 1. Purpose

Clean-room BSD design for `VRP_AR_WPNav`, functional parity with ArduPilot `AR_WPNav`.

## 2. Architecture

Baseline implementation present; integrated via `LibraryCore::tick()`. Roadmap phase **18** per `docs/CERTIFICATION_ROADMAP.md`.

## 3. Data flow

Integrated through `LibraryCore` uORB `aux/*` telemetry unless promoted to vehicle core.
HAL boundary: `src/hal/` for board-specific I/O.

## 4. Safety constraints (DAL B)

- MC/DC on safety paths
- No dynamic heap
- Bounded WCET
- MISRA subset

Hazardous failure — MC/DC on safety paths, no heap, bounded WCET.

## 5. Interface summary

| API | Description |
|---|---|
| `VRP_AR_WPNav::init(double cruise_speed_m_s, double wp_radius_m)` | Public API |
| `VRP_AR_WPNav::set_loiter_center(const Waypoint &center)` | Public API |
| `VRP_AR_WPNav::update(const LocalPosition &pos, const Attitude &attitude, const Waypoint &target,
                       const Waypoint &prev, const std::string &mode, bool active)` | Public API |
| `VRP_AR_WPNav::format_ar_wpnav(const ArWpNavOutput &o)` | Public API |

## 6. Verification

Tests: see LLRD `tests:` field and phase runner `test/libraries/run_phase18_tests.py`.
SVCP target: `test/libraries/VRP_AR_WPNav/`
