#!/usr/bin/env python3
"""Phase 9 tests: ADSB, LandingGear, MSP, MAVLink PARAM/HOME, DDS bridge."""

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
    assert "ADSB icao=" in quad
    assert "MSP seq=" in quad
    assert "GEAR retracted" in quad

    param = run([str(sitl_exe), "--vehicle", "quad", "--once", "--test-mavlink-param"])
    assert "param_req id=NAV_SPEED" in param
    assert "param=NAV_SPEED" in param
    assert "home=1" in param
    assert "param_set id=NAV_SPEED" in param

    landing = run([str(sitl_exe), "--vehicle", "quad", "--once", "--test-landing"])
    assert "GEAR deployed" in landing

    dds = run([str(sitl_exe), "--vehicle", "quad", "--once", "--enable-dds"])
    assert "DDS /vrp/out/vehicle_status" in dds

    print("VRP-LIB-PHASE9 PASS")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
