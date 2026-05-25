# Certification pack — VRP_GPS

| Field | Value |
|---|---|
| ArduPilot equivalent | `AP_GPS` |
| VR-Pilot module | `VRP_GPS` |
| Parent HLRD | `VRP-HLRD-001` |
| DAL | **B** |
| Status | **partial** |
| Implementation phase | **2** |
| License | BSD-3-Clause (clean-room) |

## DO-178C / EASA SAIL IV artifacts

| Artifact | Path | Stato |
|---|---|---|
| LLRD | [`VRP-LLRD-AP_GPS.yaml`](VRP-LLRD-AP_GPS.yaml) | baseline |
| SDD | [`VRP-SDD-AP_GPS.md`](VRP-SDD-AP_GPS.md) | template |
| SVCP tests | `test/libraries/VRP_GPS/` | planned |
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
- [ ] Unit test interfaccia pubblica (`test/libraries/VRP_GPS/`)
- [ ] Regressione SITL/HIL dove applicabile
- [ ] Riga traceability in `VRP-RTM-001.md`
- [ ] Static analysis / MISRA pulito per scope DAL
- [ ] Evidence MC/DC (DAL A/B) o statement coverage (DAL C)

## Implementazione

Codice sorgente: `src/libraries/VRP_GPS/`

Rigenerare baseline cert: `python3 Tools/cert/gen_parity_and_libraries.py`
