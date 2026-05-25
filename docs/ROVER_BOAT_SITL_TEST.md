# Test funzionale SITL Rover / Boat / Sailboat con QGroundControl

Guida operativa per verificare navigazione AR, telemetria MAVLink e missione da GCS.

## Prerequisiti

- Build SITL: `cmake -S . -B build/sitl -DVRP_BOARD=sitl && cmake --build build/sitl`
- [QGroundControl](https://qgroundcontrol.com/) installato
- Porta UDP **14550** libera

## Avvio rapido

| Veicolo   | Comando                              | Tipo MAVLink |
|-----------|--------------------------------------|--------------|
| Boat      | `./Tools/sitl_qgc.sh boat calcio`    | 11 (barca)   |
| Rover     | `./Tools/sitl_qgc.sh rover calcio`   | 10 (rover)   |
| Sailboat  | `./Tools/sitl_qgc.sh sailboat calcio`| 11 + WIND    |

Shortcut rover/boat: `./Tools/sitl_rover_qgc.sh boat calcio`

In QGC: **Application Settings → Comm Links → Add → UDP**, listening port **14550**, poi **Connect**.

## Librerie coinvolte

| Libreria VRP | Ruolo |
|--------------|-------|
| `VRP_AR_Motors` | skid-steer boat/rover, timone barca a vela |
| `VRP_AR_AttitudeControl` | PID sterzo / velocità |
| `VRP_AR_WPNav` | bearing, cross-track, Loiter, RTL |
| `VRP_Sailboat` | vela + timone da vento apparente |
| `VRP_WindVane` | vento simulato (sailboat) |
| `VRP_GCS_MAVLink` | HEARTBEAT, POS, VFR_HUD, WIND, missione |
| `VRP_SmartRTL` / `VRP_Rally` | log SmartRTL/Rally nel loop librerie |

## Telemetria QGC attesa

- **HEARTBEAT**: `custom_mode`, `type`, `autopilot=3`, `base_mode` con ARM
- **GLOBAL_POSITION_INT**: lat/lon, vx/vy/vz, heading
- **VFR_HUD**: groundspeed, heading, throttle
- **HOME_POSITION**: inviata al tick 1 in modalità `--gcs`
- **WIND** (solo sailboat): direzione e velocità
- **MISSION_***: upload waypoint da Plan view

## Piano test funzionale (checklist)

### 1. Link e veicolo

1. Avviare SITL con `--gcs`
2. Connettere QGC su UDP 14550
3. Verificare icona veicolo corretta (barca / rover)
4. Verificare modalità iniziale **Manual** (armed in SITL)

### 2. Manual e ARM

1. Arm da QGC (slide arm o comando)
2. In Manual muovere stick: barca/rover reagisce (log `ARMOT`, `SIM_STATE`)
3. Disarm e verificare motori a zero

### 3. Modalità da QGC

| Modalità QGC (Rover) | custom_mode | Verifica |
|----------------------|-------------|----------|
| Manual               | 0           | controllo RC stick |
| Loiter               | 5           | hold posizione (`ARWPNAV`) |
| Auto                 | 10          | missione attiva |
| RTL                  | 11          | ritorno home |

### 4. Missione Auto (boat/rover)

1. In QGC Plan, creare 2–3 waypoint vicino home **Calcio** (45.5156°N, 9.8494°E)
2. Upload mission
3. Passare in **Auto**
4. Osservare: `MISSION_CURRENT`, spostamento su mappa, `ARWPNAV active=1`
5. A missione completa: **Loiter** (comportamento AP-like)

### 5. Sailboat + vento

1. `./Tools/sitl_qgc.sh sailboat calcio`
2. Verificare messaggio **WIND** in QGC (Analyzer o MAVLink Inspector)
3. Auto: barca avanza con propulsione vela (`SAIL active=1`)
4. Loiter con vento variabile simulato

### 6. Test automatici CI

```bash
./Tools/run_sitl_tests.sh
```

Include self-test `boat`, `rover`, `sailboat` e assert su `ARMOT`, `ARWPNAV`, `MAVLINK_V2`.

## Parametri utili

| Parametro | Default boat | Default rover | Default sailboat |
|-----------|-------------|---------------|------------------|
| `*.max_speed_mps` | 6.0 | 4.0 | 4.0 |
| `nav.cruise_speed` | 2.0 | 1.5 | 1.8 |
| `nav.wp_radius` | 2.0 | 1.5 | 3.0 |
| `rover.frame_class` | 2 (boat) | 1 (rover) | 2 |
| `rover.skid_steer` | 1 | 1 | 0 |

## Troubleshooting

- **QGC non connette**: firewall macOS, porta 14550, un solo SITL in esecuzione
- **Veicolo wrong type**: ricompilare dopo cambio `--vehicle`
- **Mappa ferma**: verificare `GLOBAL_POSITION_INT` e GPS fix (`fix_type=3`)
- **Missione non parte**: arm + modalità Auto + waypoint caricati
