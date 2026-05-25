# Certification Roadmap

## Quality

- AS9100-oriented process evidence under `certification/`.
- Plans: [`VRP-PSAC-001.md`](../certification/plans/VRP-PSAC-001.md), SQAP, SDP, SVP, SCMP.

## Software Assurance (DO-178C)

- **DAL-B** target for flight-critical control paths.
- **153 LLRD** per libreria ArduPilot in `certification/libraries/`.
- **5 HLRD** + **VRP-SRS-001** in `certification/requirements/`.
- **CopterCore MLRD** in `certification/modules/CopterCore/`.
- Traceability HLRD → LLRD → MLRD → TC via [`VRP-RTM-001.md`](../certification/traceability/VRP-RTM-001.md).
- MC/DC record: [`VRP-MCDC-001.md`](../certification/verification/VRP-MCDC-001.md).

## Per-library certification

See [`docs/LIBRARY_CERTIFICATION.md`](LIBRARY_CERTIFICATION.md) for the full workflow.

Each library pack includes:

- `VRP-LLRD-<AP>.yaml` — low-level requirement with DAL, parent HLRD, objectives
- `VRP-SDD-<AP>.md` — design description (wired libs: complete; others: baseline)
- `README.md` — parity checklist and verification objectives
- `test/libraries/VRP_<Name>/test_api.py` — SVCP smoke

Regenerate full cert baseline:

```bash
python3 Tools/cert/gen_parity_and_libraries.py
python3 Tools/cert/gen_cert_complete.py
python3 Tools/cert/gen_traceability.py
./Tools/run_cert_checks.sh
```

## Regulatory (EASA SAIL IV + SORA)

- DVR package: [`VRP-DVR-MOC-PACKAGE.md`](../certification/regulatory/VRP-DVR-MOC-PACKAGE.md)
- SORA template: [`SORA_template.md`](../certification/regulatory/SORA_template.md)
- Safety assessment: [`VRP-SAF-001.md`](../certification/safety/VRP-SAF-001.md)

## Current baseline status

| Metric | Value |
|---|---|
| ArduPilot libraries mapped | 153 |
| LLRD / SDD / SVCP packs | 153 each |
| Wired flight-critical (copter loop) | 21 |
| HLRD | 5 |
| Test cases (copter suite) | 5 + per-library TC |
| DAL-B flight-critical | ~45 (see RTM DAL summary) |
| Copter SITL cert gate | `VRP-COPTER-ALL PASS` |

Status dashboard: [`certification/VRP-CERT-STATUS.md`](../certification/VRP-CERT-STATUS.md)

## Milestones

| Milestone | Status |
|---|---|
| Scaffold 153 packs | **Complete** |
| SDD without _TBD templates | **Complete** |
| CopterCore wired + cert | **Complete** |
| SVCP per library | **Complete** (smoke) |
| MC/DC DAL B manual record | **Baseline** |
| HIL VRBrain sign-off | Pending |
| Authority MoC (SAIL IV) | Pending |
