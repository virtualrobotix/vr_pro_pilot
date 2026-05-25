# VRP-SDD-CopterCore — Module Design Description

| Field | Value |
|---|---|
| Module | `CopterCore` |
| MLRD | [`VRP-MLRD-CopterCore.yaml`](VRP-MLRD-CopterCore.yaml) |
| Parent HLRD | VRP-HLRD-003 |
| DAL | B |

## Architecture

Orchestrates multicopter flight modes (Stabilize, Sport, AltHold, Loiter, Auto, RTL, Land, Guided). Integrates AC_* aux libraries and produces VehicleSetpoints for ControlCore.

## Data flow

SafetyCore + NavCore → CopterCore::build_setpoints → VehicleCore → ControlCore → VRP_Motors.

## Integrated libraries

See `docs/ARDUCOPTER_PARITY.md` wired table.

## Verification

`./Tools/run_copter_sitl_tests.sh` → VRP-COPTER-ALL PASS
