# Certificazione per libreria — VR-Pilot-PRO

Ogni libreria ArduPilot mappata 1:1 in VR-Pilot-PRO dispone di un **certification pack** dedicato, allineato a DO-178C e al percorso EASA SAIL IV.

## Struttura

```
certification/libraries/<AP_Name>/
├── README.md                 # Indice cert, checklist parità, obiettivi DAL
├── VRP-LLRD-<AP_Name>.yaml   # Requisito low-level (LLRD)
└── VRP-SDD-<AP_Name>.md      # Software Design Description (template → implementazione)
```

Codice corrispondente (clean-room BSD):

```
src/libraries/VRP_<Name>/
├── VRP_<Name>.h              # Header con tag @dal, @req, @parity
└── VRP_<Name>.cpp
```

## Assegnazione DAL

| DAL | Categoria tipica | Obiettivo verifica |
|:---:|---|---|
| **B** | Flight-critical: AHRS, EKF, arming, mission, controllo attitudine, HAL ChibiOS | MC/DC su path safety, no heap, WCET bounded |
| **C** | Sensori, comms, DroneCAN, storage | Statement coverage, test requirements-based |
| **D** | Stats, tuning, scripting | Unit test API pubblica |
| **E** | Telemetria hobby, HAL non target | Smoke test |
| **N/A** | Solo documentazione (`doc`) | Review documentale |

Mapping completo: [`PARITY_1TO1_MATRIX.md`](PARITY_1TO1_MATRIX.md) e [`certification/LIBRARY_REGISTRY.json`](../certification/LIBRARY_REGISTRY.json).

## Artefatti DO-178C collegati

| Livello | Documento | Percorso |
|---|---|---|
| Sistema | PSAC | `certification/plans/PSAC.md` |
| Qualità | SQAP | `certification/plans/SQAP.md` |
| High-level | HLRD | `certification/requirements/VRP-HLRD-*.yaml` |
| Low-level | LLRD (153) | `certification/libraries/*/VRP-LLRD-*.yaml` |
| Design | SDD | `certification/libraries/*/VRP-SDD-*.md` |
| Module design | SDD/MLRD | `certification/modules/CopterCore/` |
| Test cases | VRP-TC | `certification/test_cases/` |
| Traceability | RTM | `certification/traceability/VRP-RTM-001.md` |
| Accomplishment | SAS | `certification/verification/VRP-SAS-001.md` |
| MC/DC | VRP-MCDC | `certification/verification/VRP-MCDC-001.md` |

Parent HLRD:

- **VRP-HLRD-001** — heartbeat + attitude control (DAL B)
- **VRP-HLRD-002** — major/minor aux libraries (DAL C–E)
- **VRP-HLRD-003** — multicopter modes via CopterCore (DAL B)
- **VRP-HLRD-004** — safety / failsafe / avoidance (DAL B)
- **VRP-HLRD-005** — navigation / mission (DAL B)

SRS standard: [`VRP-SRS-001.md`](../certification/requirements/VRP-SRS-001.md)

## Workflow implementazione certificabile

1. **Baseline** — `python3 Tools/cert/gen_parity_and_libraries.py` + `gen_cert_complete.py`
2. **Design** — SDD wired libs complete; review before DAL B code changes
3. **Implementazione** — clean-room in `src/libraries/`, header con `@req VRP-LLRD-*`
4. **Verifica** — SVCP `test/libraries/VRP_*/test_api.py` + SITL (`run_copter_sitl_tests.sh`)
5. **Traceability** — `python3 Tools/cert/gen_traceability.py` → RTM aggiornata
6. **Gate** — `./Tools/run_cert_checks.sh` → `VRP-CERT-CHECKS PASS`

## Tooling CI

- Build SITL con tutte le librerie stub collegate via CMake `GLOB`
- Job `cert-traceability`: genera RTM da HLRD + LLRD
- Job `cert-libraries`: verifica registry e parità file

## Riferimenti

- [CERTIFICATION_ROADMAP.md](CERTIFICATION_ROADMAP.md)
- [PARITY_1TO1_MATRIX.md](PARITY_1TO1_MATRIX.md)
- [certification/libraries/INDEX.md](../certification/libraries/INDEX.md)
