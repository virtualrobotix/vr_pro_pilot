# Certification pack — VRP_CRSF

| Field | Value |
|---|---|
| Library ID | `AP_CRSF` |
| VR-Pilot module | `VRP_CRSF` |
| Parent HLRD | `VRP-HLRD-002` |
| DAL | **E** |
| Status | **partial** |
| Implementation phase | **11** |
| License | BSD-3-Clause (clean-room) |

## DO-178C / EASA SAIL IV artifacts

| Artifact | Path | Stato |
|---|---|---|
| LLRD | [`VRP-LLRD-AP_CRSF.yaml`](VRP-LLRD-AP_CRSF.yaml) | baseline |
| SDD | [`VRP-SDD-AP_CRSF.md`](VRP-SDD-AP_CRSF.md) | **baseline** |
| SVCP tests | `test/libraries/VRP_CRSF/` | **present** |
| Traceability | [`VRP-RTM-001.md`](../traceability/VRP-RTM-001.md) | auto-gen |

## Obiettivi DAL E

No safety effect — best-effort tests.

### Obiettivi verifica

- Smoke tests
- Best-effort review

## Checklist verifica

- [ ] API surface documentata vs requisiti LLRD
- [ ] Unit test interfaccia pubblica (`test/libraries/VRP_CRSF/`)
- [ ] Regressione SITL/HIL dove applicabile
- [ ] Riga traceability in `VRP-RTM-001.md`
- [ ] Static analysis / MISRA pulito per scope DAL
- [ ] Evidence MC/DC (DAL A/B) o statement coverage (DAL C)

## Implementazione

Codice sorgente: `src/libraries/VRP_CRSF/`

Rigenerare baseline cert: `python3 Tools/cert/gen_parity_and_libraries.py`
