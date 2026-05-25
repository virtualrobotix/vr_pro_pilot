#!/usr/bin/env python3
"""Phase 13 tests: mount, gripper, parachute, relay, winch, telem, notify, rtc."""

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
        "MOUNT yaw=",
        "GRIPPER state=",
        "PARACHUTE deployed=",
        "RELAY ch1=",
        "WINCH line=",
        "IBUS seq=",
        "DEVO seq=",
        "SERVO_TELEM pos=",
        "NOTIFY seq=",
        "RTC utc_ms=",
    ):
        assert token in quad, token

    failsafe = run([str(sitl_exe), "--vehicle", "quad", "--once", "--test-failsafe"])
    assert "PARACHUTE deployed=1" in failsafe
    assert "NOTIFY" in failsafe

    print("VRP-LIB-PHASE13 PASS")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
