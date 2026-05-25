# VRP-SDD-AP_GPS — Software Design Description

| Field | Value |
|---|---|
| Module | `VRP_GPS` |
| LLRD | [`VRP-LLRD-AP_GPS.yaml`](VRP-LLRD-AP_GPS.yaml) |
| DAL | B |
| Status | partial |
| Phase | 2 |

## 1. Purpose

Clean-room BSD design for `VRP_GPS`, functional parity with ArduPilot `AP_GPS`.

## 2. Architecture

Baseline implementation present; integrated via `LibraryCore::tick()`. Roadmap phase **2** per `docs/CERTIFICATION_ROADMAP.md`.

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
| `VRP_GPS::init(double origin_lat_deg, double origin_lon_deg)` | Public API |
| `VRP_GPS::update(const GpsInput &in, uint64_t time_us)` | Public API |

## 6. Verification

Tests: see LLRD `tests:` field and phase runner `test/libraries/run_phase2_tests.py`.
SVCP target: `test/libraries/VRP_GPS/`
