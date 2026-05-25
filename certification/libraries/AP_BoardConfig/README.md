# Certification pack — VRP_BoardConfig

| Field | Value |
|---|---|
| ArduPilot equivalent | `AP_BoardConfig` |
| VR-Pilot module | `VRP_BoardConfig` |
| Parent HLRD | `VRP-HLRD-002` |
| DAL | **C** |
| Status | **partial** |
| Implementation phase | **17** |
| License | BSD-3-Clause (clean-room) |

## DO-178C / EASA SAIL IV artifacts

| Artifact | Path | Stato |
|---|---|---|
| LLRD | [`VRP-LLRD-AP_BoardConfig.yaml`](VRP-LLRD-AP_BoardConfig.yaml) | baseline |
| SDD | [`VRP-SDD-AP_BoardConfig.md`](VRP-SDD-AP_BoardConfig.md) | template |
| SVCP tests | `test/libraries/VRP_BoardConfig/` | planned |
| Traceability | [`VRP-RTM-001.md`](../traceability/VRP-RTM-001.md) | auto-gen |

## Obiettivi DAL C

Major failure — requirements + tests + review; structural coverage target 100% statement.

### Obiettivi verifica

- Statement coverage 100%
- Requirements-based tests
- Design review

## Parity checklist (1:1 ArduPilot)

- [ ] API surface documentata vs comportamento ArduPilot
- [ ] Unit test interfaccia pubblica (`test/libraries/VRP_BoardConfig/`)
- [ ] Regressione SITL/HIL dove applicabile
- [ ] Riga traceability in `VRP-RTM-001.md`
- [ ] Static analysis / MISRA pulito per scope DAL
- [ ] Evidence MC/DC (DAL A/B) o statement coverage (DAL C)

## Implementazione

Codice sorgente: `src/libraries/VRP_BoardConfig/`

Rigenerare baseline cert: `python3 Tools/cert/gen_parity_and_libraries.py`
