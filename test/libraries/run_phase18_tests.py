#!/usr/bin/env python3
"""Phase 18 tests: autorotation, navigation, inertial nav, ext AHRS, NavEKF, internal error, AR, HAL."""

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
        "AUTOROT active=1",
        "NAV mode=Auto active=1",
        "INERTNAV vx=",
        "XAHRS roll=",
        "NAVEKF states=24",
        "INTERR code=0",
        "ARMOT active=1",
        "ARWPNAV active=1",
        "HALLX ok=1",
        "HALEMPTY ok=1",
    ):
        assert token in quad, token

    boat = run([str(sitl_exe), "--vehicle", "boat", "--once"])
    assert "ARMOT active=1" in boat
    assert "ARWPNAV active=1" in boat

    print("VRP-LIB-PHASE18 PASS")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
