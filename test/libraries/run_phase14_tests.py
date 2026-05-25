#!/usr/bin/env python3
"""Phase 14 tests: camera, network, generator, vtx, viso, temp, serial, fs, menu."""

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
        "CAMERA rec=",
        "NETWORK up=",
        "GENERATOR run=",
        "VTX active=",
        "VISO vx=",
        "TEMP imu=",
        "SERIAL p1=",
        "FS mounted=",
        "MENU item=",
    ):
        assert token in quad, token

    mavlink = run([str(sitl_exe), "--vehicle", "quad", "--once", "--test-mavlink-rx"])
    assert "NETWORK up=1" in mavlink

    print("VRP-LIB-PHASE14 PASS")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
