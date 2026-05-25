# Certification pack — VRP_Logger

| Field | Value |
|---|---|
| Library ID | `AP_Logger` |
| VR-Pilot module | `VRP_Logger` |
| Parent HLRD | `VRP-HLRD-001` |
| DAL | **B** |
| Status | **partial** |
| Implementation phase | **1** |
| License | BSD-3-Clause (clean-room) |

## DO-178C / EASA SAIL IV artifacts

| Artifact | Path | Stato |
|---|---|---|
| LLRD | [`VRP-LLRD-AP_Logger.yaml`](VRP-LLRD-AP_Logger.yaml) | baseline |
| SDD | [`VRP-SDD-AP_Logger.md`](VRP-SDD-AP_Logger.md) | template |
| SVCP tests | `test/libraries/VRP_Logger/` | planned |
| Traceability | [`VRP-RTM-001.md`](../traceability/VRP-RTM-001.md) | auto-gen |

## Obiettivi DAL B

Hazardous failure — MC/DC on safety paths, no heap, bounded WCET.

### Obiettivi verifica

- MC/DC on safety paths
- No dynamic heap
- Bounded WCET
- MISRA subset

## Checklist verifica

- [ ] API surface documentata vs requisiti LLRD
- [ ] Unit test interfaccia pubblica (`test/libraries/VRP_Logger/`)
- [ ] Regressione SITL/HIL dove applicabile
- [ ] Riga traceability in `VRP-RTM-001.md`
- [ ] Static analysis / MISRA pulito per scope DAL
- [ ] Evidence MC/DC (DAL A/B) o statement coverage (DAL C)

## Implementazione

Codice sorgente: `src/libraries/VRP_Logger/`

Rigenerare baseline cert: `python3 Tools/cert/gen_parity_and_libraries.py`
