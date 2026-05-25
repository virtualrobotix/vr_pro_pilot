# Certification pack — VRP_AC_PrecLand

| Field | Value |
|---|---|
| Library ID | `AC_PrecLand` |
| VR-Pilot module | `VRP_AC_PrecLand` |
| Parent HLRD | `VRP-HLRD-001` |
| DAL | **B** |
| Status | **partial** |
| Implementation phase | **17** |
| License | BSD-3-Clause (clean-room) |

## DO-178C / EASA SAIL IV artifacts

| Artifact | Path | Stato |
|---|---|---|
| LLRD | [`VRP-LLRD-AC_PrecLand.yaml`](VRP-LLRD-AC_PrecLand.yaml) | baseline |
| SDD | [`VRP-SDD-AC_PrecLand.md`](VRP-SDD-AC_PrecLand.md) | template |
| SVCP tests | `test/libraries/VRP_AC_PrecLand/` | planned |
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
- [ ] Unit test interfaccia pubblica (`test/libraries/VRP_AC_PrecLand/`)
- [ ] Regressione SITL/HIL dove applicabile
- [ ] Riga traceability in `VRP-RTM-001.md`
- [ ] Static analysis / MISRA pulito per scope DAL
- [ ] Evidence MC/DC (DAL A/B) o statement coverage (DAL C)

## Implementazione

Codice sorgente: `src/libraries/VRP_AC_PrecLand/`

Rigenerare baseline cert: `python3 Tools/cert/gen_parity_and_libraries.py`
