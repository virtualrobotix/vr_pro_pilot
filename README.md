# vr_pro_pilot

**Virtual Robotix Pro Pilot** — autopilota BSD con architettura veicolo stile ArduPilot e middleware modulare stile PX4.

Repository ufficiale: [github.com/virtualrobotix/vr_pro_pilot](https://github.com/virtualrobotix/vr_pro_pilot)

## Panoramica

VR Pro Pilot (`VR-Pilot-PRO`) è un rewrite clean-room BSD che mira alla parità 1:1 con le 153 librerie ArduPilot, con triplo target runtime:

- **SITL POSIX** — simulazione e validazione CI
- **ChibiOS** — target embedded STM32 (VRBrain, VRUBrain, VRCore)
- **ESP32** — target embedded Espressif (`VREsp32-v1`)

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
| ChibiOS | `-DVRP_TARGET_CHIBIOS=ON -DVRP_BOARD=VRBrain-v54` | HAL STM32 embedded |
| ESP32 | `-DVRP_TARGET_ESP32=ON -DVRP_BOARD=VREsp32-v1` | HAL ESP32 embedded |
| Veicoli | `-DVRP_VEHICLE=quad\|boat\|vtol\|subsea` | Profili veicolo |

### Schede hardware

| Board | APJ ID | Stato |
|---|---:|---|
| VRBrain-v51 | 1151 | hwdef scaffold |
| VRBrain-v52 | 1152 | hwdef scaffold |
| VRBrain-v54 | 1154 | hwdef scaffold |
| VRCore-v10 | 1910 | hwdef scaffold |
| VRUBrain-v51 | 1351 | hwdef scaffold |
| VREsp32-v1 | 1851 | hwdef + HAL_ESP32 |

Vedi [`docs/BOARD_VRBRAIN.md`](docs/BOARD_VRBRAIN.md) e [`docs/BOARD_ESP32.md`](docs/BOARD_ESP32.md).

## Test SITL

Il target **SITL POSIX** (`-DVRP_BOARD=sitl`) consente di validare stack, librerie e protocollo MAVLink senza hardware. È il percorso usato in CI e per lo sviluppo locale.

### Build e smoke test

```bash
# Quad (default)
cmake -S . -B build/sitl -DVRP_BOARD=sitl -DVRP_VEHICLE=quad
cmake --build build/sitl
./build/sitl/vrp_sitl --vehicle quad --model vrp_iris --once

# Boat
./Tools/sitl_run.sh boat

# VTOL
cmake -S . -B build/sitl -DVRP_BOARD=sitl -DVRP_VEHICLE=vtol
cmake --build build/sitl
./build/sitl/vrp_sitl --vehicle vtol --model vrp_standard_vtol --once
```

Un run con `--once` esegue un ciclo completo di self-test e stampa marker di stato (`VRP_SELF_TEST_PASS`, heartbeat MAVLink, sensori, controllo, ecc.).

### Suite di regressione completa

```bash
make test_sitl
# oppure
./Tools/run_sitl_tests.sh
```

Lo script compila SITL e lancia scenari automatizzati: quad/boat, MAVLink RX/mode/mission/upload/param, failsafe, landing, DDS/uxrce, ADSB avoidance, flash, HAL ChibiOS/ESP32 smoke, VTOL. Verifica l'output con assert Python e stampa i casi `VRP-TST-*` (vedi [`test/sitl/TEST_PLAN.md`](test/sitl/TEST_PLAN.md)).

### Integrazione con QGroundControl

```bash
./Tools/sitl_qgc.sh quad calcio
```

Avvia SITL in loop continuo con MAVLink UDP sulla porta **14550**. In QGroundControl: *Comm Links → UDP → Connect*.

### Flag utili di `vrp_sitl`

| Flag | Descrizione |
|---|---|
| `--once` | Esegue un ciclo e termina (CI/smoke) |
| `--gcs` | Loop continuo per GCS |
| `--vehicle quad\|boat\|vtol\|subsea` | Profilo veicolo |
| `--model vrp_iris\|vrp_boat\|…` | Modello FDM |
| `--home <name>` | Posizione home (es. `calcio`) |
| `--test-mavlink-*` | Scenari MAVLink dedicati |
| `--test-failsafe` / `--test-landing` | Scenari safety |
| `--chibios` / `--esp32` | Smoke HAL embedded via SITL |

Report di validazione: [`docs/SITL_V1_VALIDATION_REPORT.md`](docs/SITL_V1_VALIDATION_REPORT.md).

### Test librerie (SVCP)

```bash
python3 test/libraries/run_all_library_tests.py
```

Suite unitaria per modulo in `test/libraries/VRP_*/`, collegata ai LLRD di certificazione.

## Certificazione software

VR-Pilot-PRO segue un percorso **DO-178C** (target DAL-B sui path flight-critical) e **EASA SAIL IV**, con evidenze sotto `certification/`.

### Piano e processo

| Documento | Percorso | Contenuto |
|---|---|---|
| PSAC | [`certification/plans/VRP-PSAC-001.md`](certification/plans/VRP-PSAC-001.md) | Piano Software Aspects of Certification |
| SQAP | [`certification/plans/VRP-SQAP-001.md`](certification/plans/VRP-SQAP-001.md) | Piano assicurazione qualità software |
| SDP | [`certification/plans/VRP-SDP-001.md`](certification/plans/VRP-SDP-001.md) | Piano di sviluppo software |
| SVP | [`certification/plans/VRP-SVP-001.md`](certification/plans/VRP-SVP-001.md) | Piano di verifica software |
| SCMP | [`certification/plans/VRP-SCMP-001.md`](certification/plans/VRP-SCMP-001.md) | Piano configurazione e gestione change |

Roadmap e milestone: [`docs/CERTIFICATION_ROADMAP.md`](docs/CERTIFICATION_ROADMAP.md).

### Requisiti e traceability

| Livello | Documento | Percorso |
|---|---|---|
| High-level (HLRD) | VRP-HLRD-001 / 002 | [`certification/requirements/`](certification/requirements/) |
| Low-level (LLRD) | 153 pack libreria | [`certification/libraries/*/VRP-LLRD-*.yaml`](certification/libraries/) |
| Design (SDD) | Template per modulo | [`certification/libraries/*/VRP-SDD-*.md`](certification/libraries/) |
| Traceability (RTM) | Matrice HLRD → LLRD → test | [`certification/traceability/VRP-RTM-001.md`](certification/traceability/VRP-RTM-001.md) |
| Registry | Indice machine-readable | [`certification/LIBRARY_REGISTRY.json`](certification/LIBRARY_REGISTRY.json) |

- **VRP-HLRD-001** — requisiti flight-critical (librerie DAL A/B)
- **VRP-HLRD-002** — requisiti major/minor (librerie DAL C–E)

Indice di tutte le 153 librerie: [`certification/libraries/INDEX.md`](certification/libraries/INDEX.md). Ogni cartella contiene `README.md` (checklist DAL), LLRD e SDD.

Guida operativa completa: [`docs/LIBRARY_CERTIFICATION.md`](docs/LIBRARY_CERTIFICATION.md). Matrice implementazione: [`docs/PARITY_1TO1_MATRIX.md`](docs/PARITY_1TO1_MATRIX.md).

### Workflow certificazione

1. Rigenerare baseline: `python3 Tools/cert/gen_parity_and_libraries.py`
2. Completare SDD e implementazione clean-room in `src/libraries/`
3. Scrivere test SVCP in `test/libraries/VRP_*/` e aggiornare LLRD
4. Aggiornare RTM: `python3 Tools/cert/gen_traceability.py`
5. Eseguire regressione SITL: `./Tools/run_sitl_tests.sh`

La CI (`.github/workflows/ci.yml`) include job di build SITL, traceability cert e parity librerie.

## Script e tooling

```bash
./Tools/sitl_run.sh
./Tools/run_sitl_tests.sh
python3 test/libraries/run_all_library_tests.py
python3 Tools/cert/gen_parity_and_libraries.py
python3 Tools/cert/gen_traceability.py
```

## Struttura del repository

```
boards/          Definizioni hwdef per schede VR
certification/   Pack certificazione e registry librerie (153)
docs/            Architettura, parity matrix, standard
modules/ChibiOS/ Placeholder submodule RTOS (STM32)
modules/ESP-IDF/  Placeholder submodule SDK (ESP32)
src/             HAL, middleware, moduli core, librerie, veicoli
test/            Test SITL e suite librerie
Tools/           Script build, cert, parser hwdef
```

## CI

GitHub Actions (`.github/workflows/ci.yml`): build SITL, test integrazione, parity librerie, shape check ChibiOS e traceability certificazione.

## Licenza

BSD 3-Clause — vedi [`LICENSE`](LICENSE).
