# Certification pack — VRP_VisualOdom

| Field | Value |
|---|---|
| Library ID | `AP_VisualOdom` |
| VR-Pilot module | `VRP_VisualOdom` |
| Parent HLRD | `VRP-HLRD-002` |
| DAL | **C** |
| Status | **partial** |
| Implementation phase | **14** |
| License | BSD-3-Clause (clean-room) |

## DO-178C / EASA SAIL IV artifacts

| Artifact | Path | Stato |
|---|---|---|
| LLRD | [`VRP-LLRD-AP_VisualOdom.yaml`](VRP-LLRD-AP_VisualOdom.yaml) | baseline |
| SDD | [`VRP-SDD-AP_VisualOdom.md`](VRP-SDD-AP_VisualOdom.md) | **baseline** |
| SVCP tests | `test/libraries/VRP_VisualOdom/` | **present** |
| Traceability | [`VRP-RTM-001.md`](../traceability/VRP-RTM-001.md) | auto-gen |

## Obiettivi DAL C

Major failure — requirements + tests + review; structural coverage target 100% statement.

### Obiettivi verifica

- Statement coverage 100%
- Requirements-based tests
- Design review

## Checklist verifica

- [ ] API surface documentata vs requisiti LLRD
- [ ] Unit test interfaccia pubblica (`test/libraries/VRP_VisualOdom/`)
- [ ] Regressione SITL/HIL dove applicabile
- [ ] Riga traceability in `VRP-RTM-001.md`
- [ ] Static analysis / MISRA pulito per scope DAL
- [ ] Evidence MC/DC (DAL A/B) o statement coverage (DAL C)

## Implementazione

Codice sorgente: `src/libraries/VRP_VisualOdom/`

Rigenerare baseline cert: `python3 Tools/cert/gen_parity_and_libraries.py`
