# Certification pack — VRP_RangeFinder

| Field | Value |
|---|---|
| Library ID | `AP_RangeFinder` |
| VR-Pilot module | `VRP_RangeFinder` |
| Parent HLRD | `VRP-HLRD-002` |
| DAL | **C** |
| Status | **partial** |
| Implementation phase | **8** |
| License | BSD-3-Clause (clean-room) |

## DO-178C / EASA SAIL IV artifacts

| Artifact | Path | Stato |
|---|---|---|
| LLRD | [`VRP-LLRD-AP_RangeFinder.yaml`](VRP-LLRD-AP_RangeFinder.yaml) | baseline |
| SDD | [`VRP-SDD-AP_RangeFinder.md`](VRP-SDD-AP_RangeFinder.md) | **wired** |
| SVCP tests | `test/libraries/VRP_RangeFinder/` | **present** |
| Traceability | [`VRP-RTM-001.md`](../traceability/VRP-RTM-001.md) | auto-gen |

## Obiettivi DAL C

Major failure — requirements + tests + review; structural coverage target 100% statement.

### Obiettivi verifica

- Statement coverage 100%
- Requirements-based tests
- Design review

## Checklist verifica

- [x] API surface documentata vs requisiti LLRD
- [ ] Unit test interfaccia pubblica (`test/libraries/VRP_RangeFinder/`)
- [ ] Regressione SITL/HIL dove applicabile
- [x] Riga traceability in `VRP-RTM-001.md`
- [ ] Static analysis / MISRA pulito per scope DAL
- [ ] Evidence MC/DC (DAL A/B) o statement coverage (DAL C)

## Implementazione

Codice sorgente: `src/libraries/VRP_RangeFinder/`

Rigenerare baseline cert: `python3 Tools/cert/gen_parity_and_libraries.py`
