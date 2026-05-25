# SORA — Specific Operations Risk Assessment (Template)

## Operation

VR Pro Pilot multicopter SITL/HIL validated operations in segregated airspace.

## Ground risk class (GRC)

Initial GRC 6 → mitigations (geofence, RTL, ADSB) → residual GRC 4.

## Air risk class (ARC)

ARC-a mitigated by altitude cap, Loiter hold, avoidance overlay.

## Mitigations implemented in software

| SORA mitigation | VRP implementation | Test |
|---|---|---|
| M1 geofence | VRP_AC_Fence | VRP-TST-C03 |
| M2 contingency RTL | SmartRTL + Rally + RTL | VRP-TST-F01 |
| M3 detect and avoid | VRP_AC_Avoidance | VRP-COPTER-T04 |
| M4 lost link | Failsafe Loiter/RTL | VRP-TST-Q01 |

## Adjacent area / population

Operational limitation: line-of-sight, pilot in command, max altitude per param store.

## Status

Template populated with software evidence; operational approval external to codebase.
