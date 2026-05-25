#!/usr/bin/env python3
"""Phase 11 tests: airspeed, optical flow, RSSI, CRSF, LTM, TECS airspd."""

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
    assert "AIRSPEED spd=" in quad
    assert "FLOW fx=" in quad
    assert "RSSI pct=" in quad
    assert "CRSF seq=" in quad
    assert "LTM seq=" in quad

    vtol = run([str(sitl_exe), "--vehicle", "vtol", "--model", "vrp_standard_vtol", "--once", "--test-mavlink-mode"])
    assert "TECS" in vtol
    assert "airspd=" in vtol

    print("VRP-LIB-PHASE11 PASS")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
