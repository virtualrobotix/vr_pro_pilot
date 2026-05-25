# Certification pack — VRP_CheckFirmware

| Field | Value |
|---|---|
| ArduPilot equivalent | `AP_CheckFirmware` |
| VR-Pilot module | `VRP_CheckFirmware` |
| Parent HLRD | `VRP-HLRD-001` |
| DAL | **B** |
| Status | **partial** |
| Implementation phase | **19** |
| License | BSD-3-Clause (clean-room) |

## DO-178C / EASA SAIL IV artifacts

| Artifact | Path | Stato |
|---|---|---|
| LLRD | [`VRP-LLRD-AP_CheckFirmware.yaml`](VRP-LLRD-AP_CheckFirmware.yaml) | baseline |
| SDD | [`VRP-SDD-AP_CheckFirmware.md`](VRP-SDD-AP_CheckFirmware.md) | template |
| SVCP tests | `test/libraries/VRP_CheckFirmware/` | planned |
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
- [ ] Unit test interfaccia pubblica (`test/libraries/VRP_CheckFirmware/`)
- [ ] Regressione SITL/HIL dove applicabile
- [ ] Riga traceability in `VRP-RTM-001.md`
- [ ] Static analysis / MISRA pulito per scope DAL
- [ ] Evidence MC/DC (DAL A/B) o statement coverage (DAL C)

## Implementazione

Codice sorgente: `src/libraries/VRP_CheckFirmware/`

Rigenerare baseline cert: `python3 Tools/cert/gen_parity_and_libraries.py`
