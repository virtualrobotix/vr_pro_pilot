# VRP-DVR-MOC-PACKAGE — Design Verification Report (EASA SAIL IV)

## Applicability

Specific Category UAS — SAIL III/IV operational envelope with VR Pro Pilot autopilot.

## Means of Compliance

| MoC | Standard | VRP Evidence |
|---|---|---|
| MoC 1 | DO-178C DAL B software | PSAC, RTM, SAS, SITL copter suite |
| MoC 2 | SORA mitigation | `SORA_template.md` + SAF-001 |
| MoC 3 | HIL validation | Pending VRBrain campaign |
| MoC 4 | Operational limitations | ARDUCOPTER_PARITY gap list |

## Evidence index

| Document | Path |
|---|---|
| PSAC | `certification/plans/VRP-PSAC-001.md` |
| SQAP | `certification/plans/VRP-SQAP-001.md` |
| SVP | `certification/plans/VRP-SVP-001.md` |
| RTM | `certification/traceability/VRP-RTM-001.md` |
| SAS | `certification/verification/VRP-SAS-001.md` |
| SITL report | `certification/verification/VRP-SITL-REPORT-v1.md` |
| Safety | `certification/safety/VRP-SAF-001.md` |
| Copter tests | `Tools/run_copter_sitl_tests.sh` |
| SORA | `certification/regulatory/SORA_template.md` |

## Authority activities pending

- Formal MoC agreement with NAA
- HIL sign-off on target hardware
- Operational authorization per SORA
