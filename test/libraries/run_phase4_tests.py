#!/usr/bin/env python3
"""Phase 4 tests: WPNav, TECS, SRV channels, mission autotest."""

from __future__ import annotations

import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]


def run(cmd: list[str]) -> str:
    return subprocess.check_output(cmd, text=True, cwd=ROOT)


def main() -> int:
    exe = ROOT / "build" / "sitl" / "vrp_sitl"
    if not exe.exists():
        subprocess.run(["cmake", "-S", ".", "-B", "build/sitl"], cwd=ROOT, check=True)
        subprocess.run(["cmake", "--build", "build/sitl"], cwd=ROOT, check=True)

    boat = run([str(exe), "--vehicle", "boat", "--model", "vrp_boat", "--once"])
    assert "WPNAV" in boat and "valid=1" in boat
    assert "SRV m1=" in boat
    assert "MISSION idx=" in boat

    vtol = run([str(exe), "--vehicle", "vtol", "--model", "vrp_standard_vtol", "--once"])
    assert "TECS" in vtol
    assert "SRV" in vtol and "tilt=" in vtol

    print("VRP-LIB-PHASE4 PASS")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
