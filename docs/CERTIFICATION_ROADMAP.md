# Certification Roadmap

## Quality

- AS9100-oriented process evidence under `certification/`.
- Baseline plans: PSAC, SQAP, SDP, SVP, SCMP.

## Software Assurance

- DO-178C DAL-B target for flight-critical control paths.
- **153 LLRD** per libreria ArduPilot in `certification/libraries/`.
- Requirements traceability HLRD → LLRD → tests via `VRP-RTM-001.md`.
- MC/DC objective on DAL-B libraries; statement coverage on DAL-C.

## Per-library certification

See [`docs/LIBRARY_CERTIFICATION.md`](LIBRARY_CERTIFICATION.md) for the full workflow.

Each library pack includes:

- `VRP-LLRD-<AP>.yaml` — low-level requirement with DAL, parent HLRD, objectives
- `VRP-SDD-<AP>.md` — design description template
- `README.md` — parity checklist and verification objectives

Regenerate: `python3 Tools/cert/gen_parity_and_libraries.py`

## Regulatory

- SORA workflow and EASA SAIL IV DVR package placeholders included.

## Current baseline status

| Metric | Value |
|---|---|
| ArduPilot libraries mapped | 153 |
| VRP library stubs (`src/libraries/`) | 151 |
| Certification packs | 153 |
| DAL-B flight-critical | ~45 (see RTM DAL summary) |
| Functional parity complete | Milestone 0 scaffold only |

Next certification closure milestones: implement DAL-B safety core (phase 1), attach SVCP tests to LLRD `tests:` fields, MC/DC evidence for control/navigation paths.
