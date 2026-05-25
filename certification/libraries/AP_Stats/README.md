# Certification pack — VRP_Stats

| Field | Value |
|---|---|
| Library ID | `AP_Stats` |
| VR-Pilot module | `VRP_Stats` |
| Parent HLRD | `VRP-HLRD-002` |
| DAL | **C** |
| Status | **partial** |
| Implementation phase | **10** |
| License | BSD-3-Clause (clean-room) |

## DO-178C / EASA SAIL IV artifacts

| Artifact | Path | Stato |
|---|---|---|
| LLRD | [`VRP-LLRD-AP_Stats.yaml`](VRP-LLRD-AP_Stats.yaml) | baseline |
| SDD | [`VRP-SDD-AP_Stats.md`](VRP-SDD-AP_Stats.md) | **baseline** |
| SVCP tests | `test/libraries/VRP_Stats/` | **present** |
| Traceability | [`VRP-RTM-001.md`](../traceability/VRP-RTM-001.md) | auto-gen |

## Obiettivi DAL C

Major failure — requirements + tests + review; structural coverage target 100% statement.

### Obiettivi verifica

- Statement coverage 100%
- Requirements-based tests
- Design review

## Checklist verifica

- [ ] API surface documentata vs requisiti LLRD
- [ ] Unit test interfaccia pubblica (`test/libraries/VRP_Stats/`)
- [ ] Regressione SITL/HIL dove applicabile
- [ ] Riga traceability in `VRP-RTM-001.md`
- [ ] Static analysis / MISRA pulito per scope DAL
- [ ] Evidence MC/DC (DAL A/B) o statement coverage (DAL C)

## Implementazione

Codice sorgente: `src/libraries/VRP_Stats/`

Rigenerare baseline cert: `python3 Tools/cert/gen_parity_and_libraries.py`
