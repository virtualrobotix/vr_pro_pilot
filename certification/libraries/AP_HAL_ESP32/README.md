# Certification pack — VRP_HAL_ESP32

| Field | Value |
|---|---|
| Library ID | `AP_HAL_ESP32` |
| VR-Pilot module | `VRP_HAL_ESP32` |
| Parent HLRD | `VRP-HLRD-002` |
| DAL | **E** |
| Status | **partial** |
| Implementation phase | **20** |
| License | BSD-3-Clause (clean-room) |

## DO-178C / EASA SAIL IV artifacts

| Artifact | Path | Stato |
|---|---|---|
| LLRD | [`VRP-LLRD-AP_HAL_ESP32.yaml`](VRP-LLRD-AP_HAL_ESP32.yaml) | baseline |
| SDD | [`VRP-SDD-AP_HAL_ESP32.md`](VRP-SDD-AP_HAL_ESP32.md) | **baseline** |
| SVCP tests | `test/libraries/VRP_HAL_ESP32/` | **present** |
| Traceability | [`VRP-RTM-001.md`](../traceability/VRP-RTM-001.md) | auto-gen |

## Obiettivi DAL E

No safety effect — best-effort tests.

### Obiettivi verifica

- Smoke tests
- Best-effort review

## Checklist verifica

- [ ] API surface documentata vs requisiti LLRD
- [ ] Unit test interfaccia pubblica (`test/libraries/VRP_HAL_ESP32/`)
- [ ] Regressione SITL/HIL dove applicabile
- [ ] Riga traceability in `VRP-RTM-001.md`
- [ ] Static analysis / MISRA pulito per scope DAL
- [ ] Evidence MC/DC (DAL A/B) o statement coverage (DAL C)

## Implementazione

Codice sorgente: `src/libraries/VRP_HAL_ESP32/`

Rigenerare baseline cert: `python3 Tools/cert/gen_parity_and_libraries.py`
