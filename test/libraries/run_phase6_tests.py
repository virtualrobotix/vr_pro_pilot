#!/usr/bin/env python3
"""Phase 6 tests: mission protocol, L1 control, DroneCAN CAN bus."""

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

    mission = run([str(exe), "--vehicle", "quad", "--once", "--test-mavlink-mission"])
    assert "mission_req_list" in mission
    assert "MISSION_TX count=2" in mission
    assert "MISSION_TX item=0" in mission

    vtol = run([str(exe), "--vehicle", "vtol", "--model", "vrp_standard_vtol", "--once", "--test-mavlink-mode"])
    assert "L1 brg=" in vtol
    assert "DRONECAN can_id=0x" in vtol
    assert "CAN manager" in vtol and "frames=" in vtol

    print("VRP-LIB-PHASE6 PASS")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
