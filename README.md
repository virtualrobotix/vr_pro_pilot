# vr_pro_pilot

**Virtual Robotix Pro Pilot** — autopilota BSD con architettura veicolo stile ArduPilot e middleware modulare stile PX4.

Repository ufficiale: [github.com/virtualrobotix/vr_pro_pilot](https://github.com/virtualrobotix/vr_pro_pilot)

## Panoramica

VR Pro Pilot (`VR-Pilot-PRO`) è un rewrite clean-room BSD che mira alla parità 1:1 con le 153 librerie ArduPilot, con doppio target runtime:

- **SITL POSIX** — simulazione e validazione CI
- **ChibiOS** — target embedded per schede Virtual Robotix (VRBrain, VRUBrain, VRCore)

Stack modulare: HAL → SafetyCore → NavCore → VehicleCore → ControlCore → LibraryCore, con bus uORB-like e heartbeat MAVLink.

Documentazione di dettaglio: [`docs/ARCHITECTURE.md`](docs/ARCHITECTURE.md)

## Build rapida (SITL)

```bash
cmake -S . -B build/sitl -DVRP_BOARD=sitl -DVRP_VEHICLE=quad
cmake --build build/sitl
./build/sitl/vrp_sitl --vehicle quad --model vrp_iris --once
```

## Target supportati

| Target | CMake | Note |
|---|---|---|
| SITL | `-DVRP_BOARD=sitl` | Default, POSIX |
| ChibiOS | `-DVRP_TARGET_CHIBIOS=ON -DVRP_BOARD=VRBrain-v54` | HAL embedded |
| Veicoli | `-DVRP_VEHICLE=quad\|boat\|vtol\|subsea` | Profili veicolo |

### Schede hardware

| Board | APJ ID | Stato |
|---|---:|---|
| VRBrain-v51 | 1151 | hwdef scaffold |
| VRBrain-v52 | 1152 | hwdef scaffold |
| VRBrain-v54 | 1154 | hwdef scaffold |
| VRCore-v10 | 1910 | hwdef scaffold |
| VRUBrain-v51 | 1351 | hwdef scaffold |

Vedi [`docs/BOARD_VRBRAIN.md`](docs/BOARD_VRBRAIN.md).

## Script e test

```bash
./Tools/sitl_run.sh
./Tools/run_sitl_tests.sh
python3 test/libraries/run_all_library_tests.py
python3 Tools/cert/gen_parity_and_libraries.py
```

## Struttura del repository

```
boards/          Definizioni hwdef per schede VR
certification/   Pack certificazione e registry librerie (153)
docs/            Architettura, parity matrix, standard
modules/ChibiOS/ Placeholder submodule RTOS
src/             HAL, middleware, moduli core, librerie, veicoli
test/            Test SITL e suite librerie
Tools/           Script build, cert, parser hwdef
```

## CI

GitHub Actions (`.github/workflows/ci.yml`): build SITL, test integrazione, parity librerie, shape check ChibiOS e traceability certificazione.

## Licenza

BSD 3-Clause — vedi [`LICENSE`](LICENSE).
