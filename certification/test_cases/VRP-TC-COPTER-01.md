# VRP-TC-COPTER-01 — Flight stack self-test

| Field | Value |
|---|---|
| Parent HLRD | VRP-HLRD-003 |
| Script ID | `VRP-COPTER-T01` |
| Verify | test |
| Automation | `./Tools/run_copter_sitl_tests.sh` |

## Procedure

Run `./Tools/run_copter_sitl_tests.sh` T01; assert VRP_SELF_TEST_PASS, ATT_CTRL active.

## Pass criteria

Script prints `VRP-COPTER-T01 PASS` and `VRP-COPTER-ALL PASS`.

## Traceability

Linked LLRD: wired copter libraries in `certification/libraries/AC_*` and `AP_*`.
