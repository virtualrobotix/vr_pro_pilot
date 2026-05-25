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
| Traceability | RTM | `certification/traceability/VRP-RTM-001.md` |

Parent HLRD:

- **VRP-HLRD-001** — requisiti flight-critical (librerie DAL A/B)
- **VRP-HLRD-002** — requisiti major/minor (librerie DAL C–E)

## Workflow implementazione certificabile

1. **Baseline** — rigenerare matrice e pack: `python3 Tools/cert/gen_parity_and_libraries.py`
2. **Design** — completare `VRP-SDD-*.md` prima del codice (DAL B/C)
3. **Implementazione** — clean-room in `src/libraries/`, header con `@req VRP-LLRD-*`
4. **Verifica** — test in `test/libraries/VRP_*/`, aggiornare campo `tests:` nel LLRD
5. **Traceability** — `python3 Tools/cert/gen_traceability.py` → RTM aggiornata
6. **Review** — checklist in `certification/libraries/*/README.md`

## Tooling CI

- Build SITL con tutte le librerie stub collegate via CMake `GLOB`
- Job `cert-traceability`: genera RTM da HLRD + LLRD
- Job `cert-libraries`: verifica registry e parità file

## Riferimenti

- [CERTIFICATION_ROADMAP.md](CERTIFICATION_ROADMAP.md)
- [PARITY_1TO1_MATRIX.md](PARITY_1TO1_MATRIX.md)
- [certification/libraries/INDEX.md](../certification/libraries/INDEX.md)
