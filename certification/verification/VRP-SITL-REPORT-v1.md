# VRP-SITL-REPORT-v1

Baseline verification report — VR Pro Pilot SITL.

## Copter certification gate

| Suite | Result |
|---|---|
| `VRP-COPTER-T01` … `T05` | PASS |
| `VRP-COPTER-ALL` | PASS |
| `VRP-CERT-CHECKS` | PASS |

Automation: `./Tools/run_copter_sitl_tests.sh`, `./Tools/run_cert_checks.sh`

## Legacy SITL markers

- `VRP-TST-Q01` PASS
- `VRP-TST-Q02` PASS
- `VRP-TST-Q03` PASS
- `VRP-TST-Q04` PASS
- `VRP-TST-B01` PASS
- `VRP-TST-B02` PASS
- `VRP-TST-B03` PASS

## Evidence links

- SAS: `VRP-SAS-001.md`
- MC/DC: `VRP-MCDC-001.md`
- RTM: `VRP-RTM-001.md`
- Copter SDD wired: 21 libraries in `certification/libraries/AC_*`, `AP_*`
