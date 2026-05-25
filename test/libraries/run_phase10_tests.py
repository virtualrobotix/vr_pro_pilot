#!/usr/bin/env python3
"""Phase 10 tests: ADSB avoidance, Hott, flash, OpenDroneID, uxrce/DDS."""

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
    assert "threat=" in quad
    assert "HOTT seq=" in quad
    assert "AVOIDANCE active=" in quad
    assert "STATS loops=" in quad
    assert "OPEN_DRONE_ID seq=" in quad
    assert "FLASH base=0x" in quad

    avoid = run([str(sitl_exe), "--vehicle", "quad", "--once", "--test-adsb-avoid"])
    assert "AVOIDANCE active=1" in avoid
    assert "threat=critical" in avoid or "threat=warn" in avoid

    flash = run([str(sitl_exe), "--vehicle", "quad", "--once", "--test-flash"])
    assert "FLASH_STORAGE op=saved" in flash

    dds = run([str(sitl_exe), "--vehicle", "quad", "--once", "--enable-dds"])
    assert "/vrp/out/sensor_combined" in dds
    assert "/vrp/in/vehicle_command" in dds

    uxrce = run([str(sitl_exe), "--vehicle", "quad", "--once", "--enable-uxrce"])
    assert "UXRCE port=8888 status=connected" in uxrce

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
    assert "FLASH base=0x080E0000" in board

    print("VRP-LIB-PHASE10 PASS")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
