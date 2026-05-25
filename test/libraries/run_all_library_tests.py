#!/usr/bin/env python3
"""Run library phase tests 1–20 and verify parity registry is complete."""

from __future__ import annotations

import json
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]


def main() -> int:
    for phase in range(1, 21):
        script = ROOT / "test" / "libraries" / f"run_phase{phase}_tests.py"
        print(f"--- phase {phase} ---")
        subprocess.run([sys.executable, str(script)], cwd=ROOT, check=True)

    registry_path = ROOT / "certification" / "LIBRARY_REGISTRY.json"
    registry = json.loads(registry_path.read_text())
    assert len(registry) == 153, f"expected 153 libraries, got {len(registry)}"

    planned = sum(1 for entry in registry if entry["status"] == "planned")
    assert planned == 0, f"planned libraries remaining: {planned}"

    partial = sum(1 for entry in registry if entry["status"] == "partial")
    present = sum(1 for entry in registry if entry["status"] == "present")
    print(
        f"parity summary: present={present} partial={partial} planned={planned} total=153"
    )
    print("VRP-LIB-COMPLETE PASS")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
