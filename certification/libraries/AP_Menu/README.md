# Certification pack — VRP_Menu

| Field | Value |
|---|---|
| Library ID | `AP_Menu` |
| VR-Pilot module | `VRP_Menu` |
| Parent HLRD | `VRP-HLRD-002` |
| DAL | **D** |
| Status | **partial** |
| Implementation phase | **14** |
| License | BSD-3-Clause (clean-room) |

## DO-178C / EASA SAIL IV artifacts

| Artifact | Path | Stato |
|---|---|---|
| LLRD | [`VRP-LLRD-AP_Menu.yaml`](VRP-LLRD-AP_Menu.yaml) | baseline |
| SDD | [`VRP-SDD-AP_Menu.md`](VRP-SDD-AP_Menu.md) | template |
| SVCP tests | `test/libraries/VRP_Menu/` | planned |
| Traceability | [`VRP-RTM-001.md`](../traceability/VRP-RTM-001.md) | auto-gen |

## Obiettivi DAL D

Minor failure — requirements + unit tests.

### Obiettivi verifica

- Unit tests for public API
- Requirements traceability

## Checklist verifica

- [ ] API surface documentata vs requisiti LLRD
- [ ] Unit test interfaccia pubblica (`test/libraries/VRP_Menu/`)
- [ ] Regressione SITL/HIL dove applicabile
- [ ] Riga traceability in `VRP-RTM-001.md`
- [ ] Static analysis / MISRA pulito per scope DAL
- [ ] Evidence MC/DC (DAL A/B) o statement coverage (DAL C)

## Implementazione

Codice sorgente: `src/libraries/VRP_Menu/`

Rigenerare baseline cert: `python3 Tools/cert/gen_parity_and_libraries.py`
