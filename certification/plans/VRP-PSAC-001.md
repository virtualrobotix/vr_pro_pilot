# VRP-PSAC-001 — Plan for Software Aspects of Certification

| Field | Value |
|---|---|
| Standard | RTCA DO-178C / ED-12C |
| Target DAL | **B** (flight-critical), **C** (major), **D/E** (aux) |
| Product | VR Pro Pilot (`VR-Pilot-PRO`) |
| Version | v1.0 baseline |

## 1. Software overview

VR-Pilot-PRO is a clean-room BSD autopilot with triple HAL target (SITL, ChibiOS, ESP32).
Flight-critical paths: SafetyCore → NavCore → CopterCore/VehicleCore → ControlCore → Motors.

## 2. DAL allocation

See `certification/traceability/VRP-RTM-001.md` DAL summary (~45 DAL B libraries).

## 3. Lifecycle

| Phase | Activity | Evidence |
|---|---|---|
| Planning | PSAC, SQAP, SDP, SCMP, SVP | `certification/plans/` |
| Requirements | HLRD, LLRD, MLRD | `certification/requirements/`, `libraries/` |
| Design | SDD per library/module | `certification/libraries/`, `modules/CopterCore/` |
| Coding | MISRA subset, no heap on DAL B | `docs/CODING_STANDARDS.md`, CI build |
| Verification | SVCP, SITL, MC/DC | `test/libraries/`, `Tools/run_copter_sitl_tests.sh` |
| CM | Git + tagged releases | `VRP-SCMP-001.md` |

## 4. Tool qualification

| Tool | Use | Qual level |
|---|---|---|
| CMake / GCC / Clang | Build | TQL-5 acceptable for DAL B |
| Python test runners | Regression | TQL-5 |
| SITL (`vrp_sitl`) | Integration test | TQL-5 with manual review |

## 5. Compliance status

| Objective | Status |
|---|---|
| Requirements traceability | RTM auto-generated |
| Copter flight stack wired | VRP-COPTER-ALL PASS |
| MC/DC DAL B | Template + spot analysis (`VRP-MCDC-001.md`) |
| Authority submission | Pending (see DVR package) |
