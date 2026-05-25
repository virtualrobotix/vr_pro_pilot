#!/usr/bin/env python3
"""Phase 17 tests: autotune, precland, volz, robotis, onvif, irlock, icengine, ramtron, lightware, board."""

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
        "AUTOTUNE active=",
        "PRECLAND active=1",
        "VOLZ id=1",
        "ROBOTIS id=2",
        "ONVIF stream=1",
        "IRLOCK x=",
        "ICENGINE run=1",
        "RAMTRON ok=1",
        "LIGHTWARE dist=",
        "BOARD ok=1",
    ):
        assert token in quad, token

    mavlink = run([str(sitl_exe), "--vehicle", "quad", "--once", "--test-mavlink-rx"])
    assert "ONVIF stream=1" in mavlink

    print("VRP-LIB-PHASE17 PASS")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
