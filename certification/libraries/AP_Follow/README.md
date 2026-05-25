# Certification pack — VRP_Follow

| Field | Value |
|---|---|
| Library ID | `AP_Follow` |
| VR-Pilot module | `VRP_Follow` |
| Parent HLRD | `VRP-HLRD-002` |
| DAL | **C** |
| Status | **partial** |
| Implementation phase | **15** |
| License | BSD-3-Clause (clean-room) |

## DO-178C / EASA SAIL IV artifacts

| Artifact | Path | Stato |
|---|---|---|
| LLRD | [`VRP-LLRD-AP_Follow.yaml`](VRP-LLRD-AP_Follow.yaml) | baseline |
| SDD | [`VRP-SDD-AP_Follow.md`](VRP-SDD-AP_Follow.md) | **wired** |
| SVCP tests | `test/libraries/VRP_Follow/` | **present** |
| Traceability | [`VRP-RTM-001.md`](../traceability/VRP-RTM-001.md) | auto-gen |

## Obiettivi DAL C

Major failure — requirements + tests + review; structural coverage target 100% statement.

### Obiettivi verifica

- Statement coverage 100%
- Requirements-based tests
- Design review

## Checklist verifica

- [x] API surface documentata vs requisiti LLRD
- [ ] Unit test interfaccia pubblica (`test/libraries/VRP_Follow/`)
- [ ] Regressione SITL/HIL dove applicabile
- [x] Riga traceability in `VRP-RTM-001.md`
- [ ] Static analysis / MISRA pulito per scope DAL
- [ ] Evidence MC/DC (DAL A/B) o statement coverage (DAL C)

## Implementazione

Codice sorgente: `src/libraries/VRP_Follow/`

Rigenerare baseline cert: `python3 Tools/cert/gen_parity_and_libraries.py`
