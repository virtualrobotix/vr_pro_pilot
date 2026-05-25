#!/usr/bin/env python3
"""Phase 15 tests: OLC, CAN, BLHeli, NMEA, follow, leak, wheel, tune, torqeedo."""

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
        "OLC log=",
        "PICCOLO can=",
        "BLHELI esc=",
        "NMEA active=",
        "FOLLOW active=1",
        "LEAK sensors=",
        "WHEEL ticks=",
        "QUICKTUNE active=",
        "TUNING active=",
        "TORQEEDO on=",
    ):
        assert token in quad, token

    boat = run([str(sitl_exe), "--vehicle", "boat", "--once"])
    assert "TORQEEDO on=" in boat

    print("VRP-LIB-PHASE15 PASS")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
