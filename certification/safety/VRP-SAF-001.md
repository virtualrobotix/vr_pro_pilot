# VRP-SAF-001 — Safety Assessment (Preliminary)

## Functional hazards

| ID | Hazard | Severity | Mitigation | Verification |
|---|---|---|---|---|
| H-001 | Loss of attitude control | Major | PID limits, disarm on fence | VRP-COPTER-T01 |
| H-002 | Uncommanded motor output | Hazardous | Arm gate, spool ramp, disarm zero | VRP-MCDC-001 |
| H-003 | Fly-away on GPS loss | Major | RTL, Loiter hold, SmartRTL | VRP-TST-F01 |
| H-004 | Collision with manned traffic | Hazardous | ADSB avoidance overlay | VRP-COPTER-T04 |
| H-005 | Hard landing | Major | Landing + PrecLand phases | VRP-COPTER-T05 |

## FMEA notes

CopterCore integrates bounded setpoints (`max_tilt_rad` clamp) on all modes.
Motor output clamped [0,1] per channel in `VRP_Motors::mix_quad`.

## Residual risks

- Indoor GPS-denied without optical flow hardware
- Incomplete land detector vs ArduCopter
- See `docs/ARDUCOPTER_PARITY.md` gap section
