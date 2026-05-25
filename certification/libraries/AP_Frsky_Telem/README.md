# Certification pack — VRP_Frsky_Telem

| Field | Value |
|---|---|
| ArduPilot equivalent | `AP_Frsky_Telem` |
| VR-Pilot module | `VRP_Frsky_Telem` |
| Parent HLRD | `VRP-HLRD-002` |
| DAL | **E** |
| Status | **partial** |
| Implementation phase | **8** |
| License | BSD-3-Clause (clean-room) |

## DO-178C / EASA SAIL IV artifacts

| Artifact | Path | Stato |
|---|---|---|
| LLRD | [`VRP-LLRD-AP_Frsky_Telem.yaml`](VRP-LLRD-AP_Frsky_Telem.yaml) | baseline |
| SDD | [`VRP-SDD-AP_Frsky_Telem.md`](VRP-SDD-AP_Frsky_Telem.md) | template |
| SVCP tests | `test/libraries/VRP_Frsky_Telem/` | planned |
| Traceability | [`VRP-RTM-001.md`](../traceability/VRP-RTM-001.md) | auto-gen |

## Obiettivi DAL E

No safety effect — best-effort tests.

### Obiettivi verifica

- Smoke tests
- Best-effort review

## Parity checklist (1:1 ArduPilot)

- [ ] API surface documentata vs comportamento ArduPilot
- [ ] Unit test interfaccia pubblica (`test/libraries/VRP_Frsky_Telem/`)
- [ ] Regressione SITL/HIL dove applicabile
- [ ] Riga traceability in `VRP-RTM-001.md`
- [ ] Static analysis / MISRA pulito per scope DAL
- [ ] Evidence MC/DC (DAL A/B) o statement coverage (DAL C)

## Implementazione

Codice sorgente: `src/libraries/VRP_Frsky_Telem/`

Rigenerare baseline cert: `python3 Tools/cert/gen_parity_and_libraries.py`
