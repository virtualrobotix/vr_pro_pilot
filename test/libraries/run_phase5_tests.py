#!/usr/bin/env python3
"""Phase 5 tests: MAVLink SET_MODE, mission_current TX, APM_Control FW."""

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

    quad = run([str(exe), "--vehicle", "quad", "--once", "--test-mavlink-mode"])
    assert "cmd=SET_MODE custom=3" in quad
    assert "VEHICLE mode=Auto" in quad
    assert "mission_seq=" in quad

    vtol = run([str(exe), "--vehicle", "vtol", "--model", "vrp_standard_vtol", "--once", "--test-mavlink-mode"])
    assert "cmd=SET_MODE custom=19" in vtol
    assert "VEHICLE mode=FW" in vtol
    assert "APM_CTRL" in vtol

    print("VRP-LIB-PHASE5 PASS")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
