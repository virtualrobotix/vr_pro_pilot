# VRP-SVP-001 — Software Verification Plan

## Verification methods

| Method | Application |
|---|---|
| Test | SVCP unit, SITL integration, copter suite |
| Analysis | WCET bounds, MISRA static review |
| Review | SDD/LLRD peer review |

## Test suites

| Suite | Script | Scope |
|---|---|---|
| SITL full | `Tools/run_sitl_tests.sh` | All vehicles |
| Copter | `Tools/run_copter_sitl_tests.sh` | ArduCopter stack |
| Libraries | `test/libraries/run_all_library_tests.py` | 153 libs phases 1–20 |
| SVCP | `test/libraries/VRP_*/test_api.py` | Per-library smoke |

## Coverage objectives

- DAL B: MC/DC on safety paths (see `VRP-MCDC-001.md`)
- DAL C: 100% statement (target)
- DAL D/E: API smoke tests
