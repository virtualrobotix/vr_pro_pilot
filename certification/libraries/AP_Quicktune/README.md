# Certification pack — VRP_Quicktune

| Field | Value |
|---|---|
| Library ID | `AP_Quicktune` |
| VR-Pilot module | `VRP_Quicktune` |
| Parent HLRD | `VRP-HLRD-002` |
| DAL | **D** |
| Status | **partial** |
| Implementation phase | **15** |
| License | BSD-3-Clause (clean-room) |

## DO-178C / EASA SAIL IV artifacts

| Artifact | Path | Stato |
|---|---|---|
| LLRD | [`VRP-LLRD-AP_Quicktune.yaml`](VRP-LLRD-AP_Quicktune.yaml) | baseline |
| SDD | [`VRP-SDD-AP_Quicktune.md`](VRP-SDD-AP_Quicktune.md) | **baseline** |
| SVCP tests | `test/libraries/VRP_Quicktune/` | **present** |
| Traceability | [`VRP-RTM-001.md`](../traceability/VRP-RTM-001.md) | auto-gen |

## Obiettivi DAL D

Minor failure — requirements + unit tests.

### Obiettivi verifica

- Unit tests for public API
- Requirements traceability

## Checklist verifica

- [ ] API surface documentata vs requisiti LLRD
- [ ] Unit test interfaccia pubblica (`test/libraries/VRP_Quicktune/`)
- [ ] Regressione SITL/HIL dove applicabile
- [ ] Riga traceability in `VRP-RTM-001.md`
- [ ] Static analysis / MISRA pulito per scope DAL
- [ ] Evidence MC/DC (DAL A/B) o statement coverage (DAL C)

## Implementazione

Codice sorgente: `src/libraries/VRP_Quicktune/`

Rigenerare baseline cert: `python3 Tools/cert/gen_parity_and_libraries.py`
