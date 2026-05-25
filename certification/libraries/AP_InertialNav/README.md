# Certification pack — VRP_InertialNav

| Field | Value |
|---|---|
| ArduPilot equivalent | `AP_InertialNav` |
| VR-Pilot module | `VRP_InertialNav` |
| Parent HLRD | `VRP-HLRD-001` |
| DAL | **B** |
| Status | **partial** |
| Implementation phase | **18** |
| License | BSD-3-Clause (clean-room) |

## DO-178C / EASA SAIL IV artifacts

| Artifact | Path | Stato |
|---|---|---|
| LLRD | [`VRP-LLRD-AP_InertialNav.yaml`](VRP-LLRD-AP_InertialNav.yaml) | baseline |
| SDD | [`VRP-SDD-AP_InertialNav.md`](VRP-SDD-AP_InertialNav.md) | template |
| SVCP tests | `test/libraries/VRP_InertialNav/` | planned |
| Traceability | [`VRP-RTM-001.md`](../traceability/VRP-RTM-001.md) | auto-gen |

## Obiettivi DAL B

Hazardous failure — MC/DC on safety paths, no heap, bounded WCET.

### Obiettivi verifica

- MC/DC on safety paths
- No dynamic heap
- Bounded WCET
- MISRA subset

## Parity checklist (1:1 ArduPilot)

- [ ] API surface documentata vs comportamento ArduPilot
- [ ] Unit test interfaccia pubblica (`test/libraries/VRP_InertialNav/`)
- [ ] Regressione SITL/HIL dove applicabile
- [ ] Riga traceability in `VRP-RTM-001.md`
- [ ] Static analysis / MISRA pulito per scope DAL
- [ ] Evidence MC/DC (DAL A/B) o statement coverage (DAL C)

## Implementazione

Codice sorgente: `src/libraries/VRP_InertialNav/`

Rigenerare baseline cert: `python3 Tools/cert/gen_parity_and_libraries.py`
