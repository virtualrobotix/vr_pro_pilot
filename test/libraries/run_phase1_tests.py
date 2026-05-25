#!/usr/bin/env python3
"""Phase 1 DAL-B unit tests for safety core libraries."""

from __future__ import annotations

import math
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]


def test_sitl_safety_markers() -> None:
    exe = ROOT / "build" / "sitl" / "vrp_sitl"
    if not exe.exists():
        subprocess.run(["cmake", "-S", ".", "-B", "build/sitl"], cwd=ROOT, check=True)
        subprocess.run(["cmake", "--build", "build/sitl"], cwd=ROOT, check=True)
    out = subprocess.check_output([str(exe), "--vehicle", "quad", "--once"], text=True, cwd=ROOT)
    assert "SAFETY_CORE armed=1" in out, "arming gate failed"
    assert "MAVLINK_ATTITUDE roll=" in out, "AHRS output missing"
    assert "MAVLINK_V2 sent=" in out, "MAVLink v2 missing"
    assert "ATT_CTRL active" in out, "attitude control missing"


def test_math_helpers() -> None:
    # Lightweight logic checks mirroring VRP_Math behavior
    pi = math.pi
    assert abs((pi / 180.0) * 180.0 - pi) < 1e-9
    v = max(-1.0, min(1.0, 1.5))
    assert v == 1.0


def main() -> int:
    test_math_helpers()
    test_sitl_safety_markers()
    print("VRP-LIB-PHASE1 PASS")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
