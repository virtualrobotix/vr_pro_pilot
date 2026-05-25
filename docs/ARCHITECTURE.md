# VR-Pilot-PRO Architecture

## Core principles

- Triple target: `HAL_SITL`, `HAL_ChibiOS`, and `HAL_ESP32`.
- Same vehicle stack for both runtime backends.
- uORB-like in-process message bus for module boundaries.
- Deterministic scheduler with periodic tasks.
- Clean-room BSD rewrite with 1:1 ArduPilot library parity (153 mapped libraries).

## Runtime stack

```
FDM (simulation)
  → SafetyCore (AHRS, EKF, arming, mission, logger, sensors)
  → NavCore (WPNav, L1, TECS, SmartRTL)
  → VehicleCore (modes, RTL, land)
  → ControlCore (attitude, motors, APM_Control)
  → SRV_Channel
  → MAVLink / DroneCAN / DDS (optional)
  → LibraryCore (149 partial aux libraries, phases 1–20)
```

## Key modules

| Layer | Path | Role |
|---|---|---|
| HAL | `src/hal/` | SITL, ChibiOS, and ESP32 backends (`present`) |
| Middleware | `src/middleware/` | uORB bus, scheduler, param store |
| Safety | `src/modules/safety_core/` | Arming, sensors, failsafe, logging |
| Navigation | `src/modules/nav_core/` | Mission, WPNav, fixed-wing nav |
| Vehicle | `src/modules/vehicle_core/` | Flight modes and vehicle logic |
| Control | `src/modules/control_core/` | Attitude control and motor mix |
| Libraries | `src/libraries/` | 1:1 ArduPilot aux libraries (`partial`) |
| LibraryCore | `src/modules/library_core/` | Aggregates aux library tick + uORB `aux/*` |
| Vehicles | `src/vehicles/` | Quad, boat, VTOL, subsea profiles |
| Bridges | `src/modules/uxrce_dds_client/` | DDS / uXRCE ROS2 bridge |

## Library parity milestone

All **153** ArduPilot libraries are mapped in [`PARITY_1TO1_MATRIX.md`](PARITY_1TO1_MATRIX.md):

- **149** `partial` — real logic integrated via `LibraryCore::tick()`
- **3** `present` — HAL runtime backends in `src/hal/` (SITL, ChibiOS, ESP32)
- **0** `planned`
- **1** `n/a` — documentation only (`doc`)

Regenerate matrix and cert packs:

```bash
python3 Tools/cert/gen_parity_and_libraries.py
```

Run full library test suite:

```bash
python3 test/libraries/run_all_library_tests.py
```

## Runtime flow

1. Select HAL and vehicle from CLI args (`--chibios`, `--esp32`, or default SITL).
2. Initialize params, scheduler, safety core, and vehicle tasks.
3. Each loop tick: FDM → SafetyCore → NavCore → VehicleCore → ControlCore → LibraryCore.
4. Publish heartbeat, MAVLink, and aux library stdout markers.
5. Export pass/fail markers for SITL test scripts (`Tools/run_sitl_tests.sh`).
