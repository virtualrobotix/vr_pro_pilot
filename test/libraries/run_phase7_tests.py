#!/usr/bin/env python3
"""Phase 7 tests: SmartRTL, AdvancedFailsafe, mission upload, ChibiOS HAL."""

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

    upload = run([str(exe), "--vehicle", "quad", "--once", "--test-mavlink-upload"])
    assert "mission_upload count=2" in upload
    assert "MISSION_TX ack=0" in upload

    failsafe = run([str(exe), "--vehicle", "quad", "--once", "--test-failsafe"])
    assert "FAILSAFE reason=test_force rtl=1" in failsafe
    assert "SMART_RTL" in failsafe

    chibios = run([str(exe), "--vehicle", "quad", "--once", "--chibios"])
    assert "VRP_SELF_TEST_PASS" in chibios
    assert "hal=HAL_ChibiOS" in chibios

    print("VRP-LIB-PHASE7 PASS")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
