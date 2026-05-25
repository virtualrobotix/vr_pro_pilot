# Certification pack — VRP_HAL_Linux

| Field | Value |
|---|---|
| Library ID | `AP_HAL_Linux` |
| VR-Pilot module | `VRP_HAL_Linux` |
| Parent HLRD | `VRP-HLRD-002` |
| DAL | **E** |
| Status | **partial** |
| Implementation phase | **18** |
| License | BSD-3-Clause (clean-room) |

## DO-178C / EASA SAIL IV artifacts

| Artifact | Path | Stato |
|---|---|---|
| LLRD | [`VRP-LLRD-AP_HAL_Linux.yaml`](VRP-LLRD-AP_HAL_Linux.yaml) | baseline |
| SDD | [`VRP-SDD-AP_HAL_Linux.md`](VRP-SDD-AP_HAL_Linux.md) | template |
| SVCP tests | `test/libraries/VRP_HAL_Linux/` | planned |
| Traceability | [`VRP-RTM-001.md`](../traceability/VRP-RTM-001.md) | auto-gen |

## Obiettivi DAL E

No safety effect — best-effort tests.

### Obiettivi verifica

- Smoke tests
- Best-effort review

## Checklist verifica

- [ ] API surface documentata vs requisiti LLRD
- [ ] Unit test interfaccia pubblica (`test/libraries/VRP_HAL_Linux/`)
- [ ] Regressione SITL/HIL dove applicabile
- [ ] Riga traceability in `VRP-RTM-001.md`
- [ ] Static analysis / MISRA pulito per scope DAL
- [ ] Evidence MC/DC (DAL A/B) o statement coverage (DAL C)

## Implementazione

Codice sorgente: `src/libraries/VRP_HAL_Linux/`

Rigenerare baseline cert: `python3 Tools/cert/gen_parity_and_libraries.py`
