# VRP Certification Status

Last generated: `Tools/cert/gen_cert_complete.py`

## Standards coverage

| Standard | Artifacts | Status |
|---|---|---|
| DO-178C | PSAC, SQAP, SDP, SVP, SCMP, HLRD, LLRD, SDD, RTM, SAS, MC/DC | **Baseline complete** |
| EASA SAIL IV | DVR package, SORA template | **Evidence indexed** |
| AS9100 | SQAP process records | **Aligned** |
| MISRA | CODING_STANDARDS + DAL B checklist | **Subset defined** |
| SORA | Regulatory template + SAF-001 link | **Populated** |

## Library certification

| Metric | Count |
|---|---:|
| Libraries mapped | 153 |
| LLRD | 153 |
| SDD (no _TBD template) | 153 |
| Wired flight-critical SDD | 21 |
| SVCP packs | 153 |
| Test cases (copter suite) | 5 + per-library TC |

## Verification gates

```bash
python3 Tools/cert/gen_cert_complete.py
python3 Tools/cert/gen_traceability.py
./Tools/run_copter_sitl_tests.sh
python3 test/libraries/run_all_library_tests.py
```

Expected: `VRP-COPTER-ALL PASS`, `VRP-LIB-COMPLETE PASS`, RTM updated.

## Open for audit closure

- HIL on VRBrain-v54
- Tool-qualified MC/DC report
- Authority MoC sign-off
