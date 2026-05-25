# Certification pack — VRP_Tuning

| Field | Value |
|---|---|
| Library ID | `AP_Tuning` |
| VR-Pilot module | `VRP_Tuning` |
| Parent HLRD | `VRP-HLRD-002` |
| DAL | **D** |
| Status | **partial** |
| Implementation phase | **15** |
| License | BSD-3-Clause (clean-room) |

## DO-178C / EASA SAIL IV artifacts

| Artifact | Path | Stato |
|---|---|---|
| LLRD | [`VRP-LLRD-AP_Tuning.yaml`](VRP-LLRD-AP_Tuning.yaml) | baseline |
| SDD | [`VRP-SDD-AP_Tuning.md`](VRP-SDD-AP_Tuning.md) | **baseline** |
| SVCP tests | `test/libraries/VRP_Tuning/` | **present** |
| Traceability | [`VRP-RTM-001.md`](../traceability/VRP-RTM-001.md) | auto-gen |

## Obiettivi DAL D

Minor failure — requirements + unit tests.

### Obiettivi verifica

- Unit tests for public API
- Requirements traceability

## Checklist verifica

- [ ] API surface documentata vs requisiti LLRD
- [ ] Unit test interfaccia pubblica (`test/libraries/VRP_Tuning/`)
- [ ] Regressione SITL/HIL dove applicabile
- [ ] Riga traceability in `VRP-RTM-001.md`
- [ ] Static analysis / MISRA pulito per scope DAL
- [ ] Evidence MC/DC (DAL A/B) o statement coverage (DAL C)

## Implementazione

Codice sorgente: `src/libraries/VRP_Tuning/`

Rigenerare baseline cert: `python3 Tools/cert/gen_parity_and_libraries.py`
