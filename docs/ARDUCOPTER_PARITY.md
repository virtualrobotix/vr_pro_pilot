# Parità ArduCopter — VR Pro Pilot

Guida al mapping funzionale tra **ArduCopter** e **VR Pro Pilot** per il veicolo multicopter (`quad`).

## Architettura runtime

```
FDM → SafetyCore → NavCore → VehicleCore/CopterCore → ControlCore → VRP_Motors
```

| Modulo ArduCopter | Modulo VRP | Librerie principali |
|---|---|---|
| `Copter.cpp` loop | `CopterCore` + `main.cpp` | AC_InputManager, AC_PrecLand, AC_AutoTune, VRP_Takeoff |
| Attitude/Pos control | `ControlCore` | `VRP_AC_AttitudeControl`, `VRP_Motors` |
| WPNav / Loiter | `NavCore` | `VRP_AC_WPNav` (SCurve speed) |
| Mode / RC / Land | `VehicleCore` | `VRP_RC_Channel`, `VRP_Landing` (land detector) |
| Failsafe / Fence | `SafetyCore` | `VRP_AC_Fence`, `VRP_AC_Avoidance`, `VRP_SmartRTL`, `VRP_Terrain`, `VRP_Baro` |

## Librerie AC/AP collegate al volo quad

| Libreria | Stato | Funzione ArduCopter-like |
|---|---|---|
| `VRP_AC_AttitudeControl` | wired | PID + pos 3 assi base (jerk FF, heading hold) |
| `VRP_AC_WPNav` | wired | loiter, RTL, cross-track, **SCurve speed** |
| `VRP_AC_InputManager` | wired | RC stabilize scaling |
| `VRP_AC_Avoidance` | wired | overlay ADSB/proximity |
| `VRP_AC_PrecLand` | wired | precision land |
| `VRP_AC_AutoTune` | wired | scale PID aux1 |
| `VRP_AC_Fence` | wired | breach → RTL/SmartRTL |
| `VRP_AC_Sprayer` / `CustomControl` / `AC_PID` | wired | overlay setpoint |
| `VRP_InertialNav` / `SurfaceDistance` | wired | nav damping + AGL |
| `VRP_Follow` / `Rally` / `OpticalFlow` | wired | Follow mode, rally, FlowHold |
| `VRP_Landing` | wired | land phases + **land detector + auto-disarm** |
| `VRP_Takeoff` | wired | takeoff check + climb detect |
| `VRP_Motors` | wired | spool, yaw headroom, **thrust linearization** |
| `VRP_Terrain` / `VRP_Baro` | wired | terrain alt bias, ground effect |
| `VRP_NavEKF3` | wired | flow fusion lite, **GPS glitch recovery** |
| `VRP_SmartRTL` | wired | modo **SmartRTL** dedicato |

## Modi di volo supportati (quad)

| Modo | Comportamento VRP |
|---|---|
| Stabilize | RC → attitude |
| Sport | Stabilize tilt +20% |
| Acro | rate control |
| AltHold | alt + pos hold |
| PosHold | pos hold forte (no RC lean) |
| Loiter | hold posizione WPNav |
| Brake | decel velocity → zero |
| Auto | missione |
| RTL | ritorno home |
| SmartRTL | breadcrumb path RTL |
| Land | landing + detector |
| Guided | target GCS |
| Follow | follow target bearing |
| FlowHold | optical flow hold |

## Test SITL

```bash
./Tools/run_copter_sitl_tests.sh    # VRP-COPTER-ALL PASS
./Tools/run_cert_checks.sh          # certificazione DO-178C
./Tools/run_sitl_tests.sh           # suite completa veicoli
```

## Gap residui (post chiusura P0–P5)

| Priorità | Stato | Note residue |
|:---:|---|---|
| **P0** Controllo | **Chiuso base** | PosControl semplificato OK; no hover-learn auto |
| **P1** Modi | **Chiuso base** | 14 modi attivi; mancano Flip, Circle, ZigZag, Throw, Turtle, DroneShow, SystemID |
| **P2** Nav/Missione | **Chiuso base** | SCurve speed OK; no spline 3D, DO_JUMP/ROI completi, terrain DEM reale |
| **P3** Sensori/EKF | **Chiuso base** | flow fusion + glitch OK; no multi-lane EKF-GSF, CompassMot |
| **P4** LibraryCore | **Parziale** | payload/heli/scripting ancora aux |
| **P5** HAL/Cert | **Chiuso doc** | SITL+DO-178C baseline; HIL VRBrain pending |

### Copertura stimata aggiornata

| Categoria | vs ArduCopter |
|---|---|
| Volo base multicopter | **~85%** |
| Modi di volo | **~55%** (14/25+) |
| Navigazione missione | **~65%** |
| Stima stato (EKF) | **~55%** |
| Certificazione software | **baseline audit-ready** |
