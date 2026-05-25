#!/usr/bin/env python3
"""Phase 19 tests: custom control, input, pid, sprayer, ap avoidance, dal, fft, fw, iomcu, accelcal."""

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
        "CUSTCTL active=1",
        "INPUTM ch=5",
        "ACPID active=1",
        "SPRAYER pump=",
        "APAVOID active=1",
        "DAL level=B",
        "GYROFFT active=1",
        "FWCHK ok=1",
        "IOMCU ok=1",
        "ACCELCAL run=1",
    ):
        assert token in quad, token

    print("VRP-LIB-PHASE19 PASS")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
