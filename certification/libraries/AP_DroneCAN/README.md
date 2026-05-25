# Certification pack — VRP_DroneCAN

| Field | Value |
|---|---|
| Library ID | `AP_DroneCAN` |
| VR-Pilot module | `VRP_DroneCAN` |
| Parent HLRD | `VRP-HLRD-002` |
| DAL | **C** |
| Status | **partial** |
| Implementation phase | **6** |
| License | BSD-3-Clause (clean-room) |

## DO-178C / EASA SAIL IV artifacts

| Artifact | Path | Stato |
|---|---|---|
| LLRD | [`VRP-LLRD-AP_DroneCAN.yaml`](VRP-LLRD-AP_DroneCAN.yaml) | baseline |
| SDD | [`VRP-SDD-AP_DroneCAN.md`](VRP-SDD-AP_DroneCAN.md) | **baseline** |
| SVCP tests | `test/libraries/VRP_DroneCAN/` | **present** |
| Traceability | [`VRP-RTM-001.md`](../traceability/VRP-RTM-001.md) | auto-gen |

## Obiettivi DAL C

Major failure — requirements + tests + review; structural coverage target 100% statement.

### Obiettivi verifica

- Statement coverage 100%
- Requirements-based tests
- Design review

## Checklist verifica

- [ ] API surface documentata vs requisiti LLRD
- [ ] Unit test interfaccia pubblica (`test/libraries/VRP_DroneCAN/`)
- [ ] Regressione SITL/HIL dove applicabile
- [ ] Riga traceability in `VRP-RTM-001.md`
- [ ] Static analysis / MISRA pulito per scope DAL
- [ ] Evidence MC/DC (DAL A/B) o statement coverage (DAL C)

## Implementazione

Codice sorgente: `src/libraries/VRP_DroneCAN/`

Rigenerare baseline cert: `python3 Tools/cert/gen_parity_and_libraries.py`
