#!/usr/bin/env python3
"""Phase 8 tests: landing, rangefinder, proximity, FrSky, mission reached, ChibiOS hwdef."""

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
    assert "RANGEFINDER dist=" in quad
    assert "PROXIMITY min=" in quad
    assert "FRSKY seq=" in quad
    assert "MISSION_TX rng=" in quad

    landing = run([str(sitl_exe), "--vehicle", "quad", "--once", "--test-landing"])
    assert "cmd=SET_MODE custom=9" in landing
    assert "LAND phase=" in landing
    assert "VEHICLE mode=Land" in landing

    vrbrain_dir = ROOT / "build" / "vrbrain-v54"
    vrbrain_exe = vrbrain_dir / "vrp_sitl"
    if not vrbrain_exe.exists():
        subprocess.run(
            [
                "cmake",
                "-S",
                ".",
                "-B",
                str(vrbrain_dir),
                "-DVRP_BOARD=VRBrain-v54",
                "-DVRP_VEHICLE=quad",
                "-DVRP_TARGET_CHIBIOS=ON",
            ],
            cwd=ROOT,
            check=True,
        )
        subprocess.run(["cmake", "--build", str(vrbrain_dir)], cwd=ROOT, check=True)

    board = run([str(vrbrain_exe), "--vehicle", "quad", "--once", "--chibios"])
    assert "AP_HW_VRBRAIN_V54" in board
    assert "hal=HAL_ChibiOS" in board

    print("VRP-LIB-PHASE8 PASS")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
