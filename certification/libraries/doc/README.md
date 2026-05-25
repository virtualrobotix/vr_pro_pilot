# Certification pack — VRP_DOC

| Field | Value |
|---|---|
| ArduPilot equivalent | `doc` |
| VR-Pilot module | `VRP_DOC` |
| Parent HLRD | `VRP-HLRD-002` |
| DAL | **N/A** |
| Status | **n/a** |
| Implementation phase | **99** |
| License | BSD-3-Clause (clean-room) |

## DO-178C / EASA SAIL IV artifacts

| Artifact | Path | Stato |
|---|---|---|
| LLRD | [`VRP-LLRD-doc.yaml`](VRP-LLRD-doc.yaml) | baseline |
| SDD | [`VRP-SDD-doc.md`](VRP-SDD-doc.md) | template |
| SVCP tests | `test/libraries/VRP_DOC/` | planned |
| Traceability | [`VRP-RTM-001.md`](../traceability/VRP-RTM-001.md) | auto-gen |

## Obiettivi DAL N/A

Documentation-only; no airborne software artifact.

### Obiettivi verifica

- Documentation review only

## Parity checklist (1:1 ArduPilot)

- [ ] API surface documentata vs comportamento ArduPilot
- [ ] Unit test interfaccia pubblica (`test/libraries/VRP_DOC/`)
- [ ] Regressione SITL/HIL dove applicabile
- [ ] Riga traceability in `VRP-RTM-001.md`
- [ ] Static analysis / MISRA pulito per scope DAL
- [ ] Evidence MC/DC (DAL A/B) o statement coverage (DAL C)

## Implementazione

Codice sorgente: `src/libraries/VRP_DOC/`

Rigenerare baseline cert: `python3 Tools/cert/gen_parity_and_libraries.py`
