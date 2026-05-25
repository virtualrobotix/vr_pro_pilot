# Certification pack — VRP_Scripting

| Field | Value |
|---|---|
| ArduPilot equivalent | `AP_Scripting` |
| VR-Pilot module | `VRP_Scripting` |
| Parent HLRD | `VRP-HLRD-002` |
| DAL | **D** |
| Status | **partial** |
| Implementation phase | **3** |
| License | BSD-3-Clause (clean-room) |

## DO-178C / EASA SAIL IV artifacts

| Artifact | Path | Stato |
|---|---|---|
| LLRD | [`VRP-LLRD-AP_Scripting.yaml`](VRP-LLRD-AP_Scripting.yaml) | baseline |
| SDD | [`VRP-SDD-AP_Scripting.md`](VRP-SDD-AP_Scripting.md) | template |
| SVCP tests | `test/libraries/VRP_Scripting/` | planned |
| Traceability | [`VRP-RTM-001.md`](../traceability/VRP-RTM-001.md) | auto-gen |

## Obiettivi DAL D

Minor failure — requirements + unit tests.

### Obiettivi verifica

- Unit tests for public API
- Requirements traceability

## Parity checklist (1:1 ArduPilot)

- [ ] API surface documentata vs comportamento ArduPilot
- [ ] Unit test interfaccia pubblica (`test/libraries/VRP_Scripting/`)
- [ ] Regressione SITL/HIL dove applicabile
- [ ] Riga traceability in `VRP-RTM-001.md`
- [ ] Static analysis / MISRA pulito per scope DAL
- [ ] Evidence MC/DC (DAL A/B) o statement coverage (DAL C)

## Implementazione

Codice sorgente: `src/libraries/VRP_Scripting/`

Rigenerare baseline cert: `python3 Tools/cert/gen_parity_and_libraries.py`
