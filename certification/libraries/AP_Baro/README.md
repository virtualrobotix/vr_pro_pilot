# Certification pack — VRP_Baro

| Field | Value |
|---|---|
| ArduPilot equivalent | `AP_Baro` |
| VR-Pilot module | `VRP_Baro` |
| Parent HLRD | `VRP-HLRD-001` |
| DAL | **B** |
| Status | **partial** |
| Implementation phase | **2** |
| License | BSD-3-Clause (clean-room) |

## DO-178C / EASA SAIL IV artifacts

| Artifact | Path | Stato |
|---|---|---|
| LLRD | [`VRP-LLRD-AP_Baro.yaml`](VRP-LLRD-AP_Baro.yaml) | baseline |
| SDD | [`VRP-SDD-AP_Baro.md`](VRP-SDD-AP_Baro.md) | template |
| SVCP tests | `test/libraries/VRP_Baro/` | planned |
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
- [ ] Unit test interfaccia pubblica (`test/libraries/VRP_Baro/`)
- [ ] Regressione SITL/HIL dove applicabile
- [ ] Riga traceability in `VRP-RTM-001.md`
- [ ] Static analysis / MISRA pulito per scope DAL
- [ ] Evidence MC/DC (DAL A/B) o statement coverage (DAL C)

## Implementazione

Codice sorgente: `src/libraries/VRP_Baro/`

Rigenerare baseline cert: `python3 Tools/cert/gen_parity_and_libraries.py`
