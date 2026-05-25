# Certification pack — VRP_HAL_QURT

| Field | Value |
|---|---|
| ArduPilot equivalent | `AP_HAL_QURT` |
| VR-Pilot module | `VRP_HAL_QURT` |
| Parent HLRD | `VRP-HLRD-002` |
| DAL | **E** |
| Status | **partial** |
| Implementation phase | **20** |
| License | BSD-3-Clause (clean-room) |

## DO-178C / EASA SAIL IV artifacts

| Artifact | Path | Stato |
|---|---|---|
| LLRD | [`VRP-LLRD-AP_HAL_QURT.yaml`](VRP-LLRD-AP_HAL_QURT.yaml) | baseline |
| SDD | [`VRP-SDD-AP_HAL_QURT.md`](VRP-SDD-AP_HAL_QURT.md) | template |
| SVCP tests | `test/libraries/VRP_HAL_QURT/` | planned |
| Traceability | [`VRP-RTM-001.md`](../traceability/VRP-RTM-001.md) | auto-gen |

## Obiettivi DAL E

No safety effect — best-effort tests.

### Obiettivi verifica

- Smoke tests
- Best-effort review

## Parity checklist (1:1 ArduPilot)

- [ ] API surface documentata vs comportamento ArduPilot
- [ ] Unit test interfaccia pubblica (`test/libraries/VRP_HAL_QURT/`)
- [ ] Regressione SITL/HIL dove applicabile
- [ ] Riga traceability in `VRP-RTM-001.md`
- [ ] Static analysis / MISRA pulito per scope DAL
- [ ] Evidence MC/DC (DAL A/B) o statement coverage (DAL C)

## Implementazione

Codice sorgente: `src/libraries/VRP_HAL_QURT/`

Rigenerare baseline cert: `python3 Tools/cert/gen_parity_and_libraries.py`
