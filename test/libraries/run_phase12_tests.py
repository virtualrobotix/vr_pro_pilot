#!/usr/bin/env python3
"""Phase 12 tests: soaring, rpm, wind, terrain, rally, AIS, surface, beacon, RC/ESC telem."""

from __future__ import annotations

import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]


def run(cmd: list[str], cwd: Path | None = None) -> str:
    return subprocess.check_output(cmd, text=True, cwd=cwd or ROOT)


def main() -> int:
    sitl_exe = ROOT / "build" / "sitl" / "vrp_sitl"
    if not sitl_exe.exists():
        subprocess.run(["cmake", "-S", ".", "-B", "build/sitl"], cwd=ROOT, check=True)
        subprocess.run(["cmake", "--build", "build/sitl"], cwd=ROOT, check=True)

    quad = run([str(sitl_exe), "--vehicle", "quad", "--once"])
    for token in (
        "SOARING thermal=",
        "RPM m1=",
        "WIND spd=",
        "TERRAIN amsl=",
        "RALLY idx=",
        "AIS mmsi=",
        "SURFACE agl=",
        "BEACON id=",
        "RC_TELEM seq=",
        "ESC_TELEM volt=",
    ):
        assert token in quad, token

    boat = run([str(sitl_exe), "--vehicle", "boat", "--model", "vrp_boat", "--once"])
    assert "AIS mmsi=" in boat
    assert "RALLY idx=" in boat

    print("VRP-LIB-PHASE12 PASS")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
