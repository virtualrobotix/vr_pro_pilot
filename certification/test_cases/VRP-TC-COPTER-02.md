# VRP-TC-COPTER-02 — WPNav + POSCTL

| Field | Value |
|---|---|
| Parent HLRD | VRP-HLRD-003 |
| Script ID | `VRP-COPTER-T02` |
| Verify | test |
| Automation | `./Tools/run_copter_sitl_tests.sh` |

## Procedure

Assert ACWPNAV active=1 and POSCTL roll= in quad --once output.

## Pass criteria

Script prints `VRP-COPTER-T02 PASS` and `VRP-COPTER-ALL PASS`.

## Traceability

Linked LLRD: wired copter libraries in `certification/libraries/AC_*` and `AP_*`.
