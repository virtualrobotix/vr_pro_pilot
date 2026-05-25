# Certification pack — VRP_SmartRTL

| Field | Value |
|---|---|
| Library ID | `AP_SmartRTL` |
| VR-Pilot module | `VRP_SmartRTL` |
| Parent HLRD | `VRP-HLRD-001` |
| DAL | **B** |
| Status | **partial** |
| Implementation phase | **7** |
| License | BSD-3-Clause (clean-room) |

## DO-178C / EASA SAIL IV artifacts

| Artifact | Path | Stato |
|---|---|---|
| LLRD | [`VRP-LLRD-AP_SmartRTL.yaml`](VRP-LLRD-AP_SmartRTL.yaml) | baseline |
| SDD | [`VRP-SDD-AP_SmartRTL.md`](VRP-SDD-AP_SmartRTL.md) | **wired** |
| SVCP tests | `test/libraries/VRP_SmartRTL/` | **present** |
| Traceability | [`VRP-RTM-001.md`](../traceability/VRP-RTM-001.md) | auto-gen |

## Obiettivi DAL B

Hazardous failure — MC/DC on safety paths, no heap, bounded WCET.

### Obiettivi verifica

- MC/DC on safety paths
- No dynamic heap
- Bounded WCET
- MISRA subset

## Checklist verifica

- [x] API surface documentata vs requisiti LLRD
- [ ] Unit test interfaccia pubblica (`test/libraries/VRP_SmartRTL/`)
- [ ] Regressione SITL/HIL dove applicabile
- [x] Riga traceability in `VRP-RTM-001.md`
- [ ] Static analysis / MISRA pulito per scope DAL
- [ ] Evidence MC/DC (DAL A/B) o statement coverage (DAL C)

## Implementazione

Codice sorgente: `src/libraries/VRP_SmartRTL/`

Rigenerare baseline cert: `python3 Tools/cert/gen_parity_and_libraries.py`
