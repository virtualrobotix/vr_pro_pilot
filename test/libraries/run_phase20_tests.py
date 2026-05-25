#!/usr/bin/env python3
"""Phase 20 tests: ADC, button, CSV, rotations, DAC, declination, EFI, ext ctl, GSOF, HAL, JSON, module, heap."""

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
        "ADC ch=1 mv=",
        "BTN id=1 pressed=",
        "CSV rows=",
        "CROT yaw=",
        "DAC ch=1 val=",
        "DECL deg=",
        "EFI fuel=",
        "EXTCTL active=",
        "GSOF fix=",
        "HALESP ok=1 backend=esp32",
        "HALQURT ok=1 backend=qurt",
        "JSBTN btn=",
        "JSON keys=",
        "MODULE count=",
        "MHEAP free_kb=",
    ):
        assert token in quad, token

    print("VRP-LIB-PHASE20 PASS")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
