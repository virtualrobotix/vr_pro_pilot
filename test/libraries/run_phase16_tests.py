#!/usr/bin/env python3
"""Phase 16 tests: ROMFS, KDECAN, FETtec, radio, SBUS, LED, servo events, RC map, storage, tempcal."""

from __future__ import annotations

import subprocess
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]


def run(cmd: list[str]) -> str:
    return subprocess.check_output(cmd, text=True, cwd=ROOT)


def main() -> int:
    sitl_exe = ROOT / "build" / "sitl" / "vrp_sitl"
    if not sitl_exe.exists():
        subprocess.run(["cmake", "-S", ".", "-B", "build/sitl"], cwd=ROOT, check=True)
        subprocess.run(["cmake", "--build", "build/sitl"], cwd=ROOT, check=True)

    quad = run([str(sitl_exe), "--vehicle", "quad", "--once"])
    for token in (
        "ROMFS mounted=1",
        "KDECAN bus=1",
        "FETTEC esc=4",
        "RADIO bound=1",
        "SBUS active=1",
        "SERLED active=1",
        "SRV_EVT active=1",
        "RCMAP roll=",
        "STORAGE ready=1",
        "TEMPCAL cal=1",
    ):
        assert token in quad, token

    print("VRP-LIB-PHASE16 PASS")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
