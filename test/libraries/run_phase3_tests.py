#!/usr/bin/env python3
"""Phase 3 tests: vehicle modes, RC, OSD, scripting, VTOL."""

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

    quad = run([str(exe), "--vehicle", "quad", "--once"])
    assert "RC roll=" in quad
    assert "OSD mode=" in quad
    assert "SCRIPT" in quad
    assert "VEHICLE mode=" in quad

    vtol = run([str(exe), "--vehicle", "vtol", "--model", "vrp_standard_vtol", "--once"])
    assert "vtol_phase=TRANSITION" in vtol or "mode=Transition" in vtol
    assert "vtol_phase=FW" in vtol or "mode=FW" in vtol

    print("VRP-LIB-PHASE3 PASS")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
