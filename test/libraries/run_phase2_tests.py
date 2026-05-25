#!/usr/bin/env python3
"""Phase 2 tests: sensors, MAVLink RX, DroneCAN."""

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

    out = run([str(exe), "--vehicle", "quad", "--once"])
    assert "SENSORS GPS" in out and "BARO alt=" in out and "COMPASS hdg=" in out
    assert "MAVLINK_V2 sent=" in out
    assert "DRONECAN node=" in out

    rx = run([str(exe), "--vehicle", "quad", "--once", "--test-mavlink-rx"])
    assert "MAVLINK_RX msg=76 cmd=ARM" in rx

    print("VRP-LIB-PHASE2 PASS")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
