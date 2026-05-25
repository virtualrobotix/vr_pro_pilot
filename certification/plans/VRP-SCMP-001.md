# VRP-SCMP-001 — Software Configuration Management Plan

## Baselines

- Git repository: `virtualrobotix/vr_pro_pilot`
- Release tags: `v*.*.*` with RTM snapshot
- Submodule: ChibiOS under `modules/ChibiOS`

## Change process

1. Feature branch → PR with LLRD/SDD update if DAL B/C
2. CI green (build, SITL, cert-traceability)
3. Merge to main
4. Regenerate cert artifacts before release tag

## Identification

Each source file DAL B+ tagged with `@dal`, `@req`, `@module` in header.
