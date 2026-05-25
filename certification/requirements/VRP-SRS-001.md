# VRP-SRS-001 — Software Requirements Standard

## Scope

Defines requirement authoring, DAL assignment, and verification objectives for VR-Pilot-PRO
aligned with **DO-178C** and **EASA SAIL IV** (Specific Assurance and Integrity Level).

## Requirement levels

| Level | ID prefix | Location | Author |
|---|---|---|---|
| High-Level | VRP-HLRD-* | `certification/requirements/` | Systems |
| Low-Level (library) | VRP-LLRD-* | `certification/libraries/*/VRP-LLRD-*.yaml` | Library owner |
| Module | VRP-MLRD-* | `certification/modules/*/` | Module owner |
| Test Case | VRP-TC-* | `certification/test_cases/` | V&V |

## DAL assignment (DO-178C)

| DAL | Failure condition | Verification objectives |
|:---:|---|---|
| A | Catastrophic | MC/DC, formal methods where applicable |
| B | Hazardous | MC/DC on safety paths, no heap, bounded WCET |
| C | Major | Statement coverage, requirements-based tests |
| D | Minor | Unit tests, traceability |
| E | No effect | Smoke tests |

## SAIL IV mapping

| SAIL | VRP equivalent | Evidence |
|:---:|---|---|
| I | DAL E/D aux | Phase library tests |
| II | DAL C sensors/comms | SVCP + SITL |
| III | DAL B flight-critical | MC/DC + HIL/SITL copter suite |
| IV | DAL A/B + ops | DVR package + SORA |

## Standards referenced

- RTCA DO-178C / EUROCAE ED-12C
- EASA SAIL (Specific Category UAS)
- AS9100 process evidence (`VRP-SQAP-001.md`)
- MISRA C++ subset (DAL B paths)
- SORA (`certification/regulatory/SORA_template.md`)

## Change control

All requirement changes require RTM regeneration:

```bash
python3 Tools/cert/gen_parity_and_libraries.py
python3 Tools/cert/gen_cert_complete.py
python3 Tools/cert/gen_traceability.py
```
