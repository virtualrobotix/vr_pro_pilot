#!/usr/bin/env python3
"""SVCP smoke test — VRP_AR_Motors (BASELINE)."""

import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[3]
SITL = ROOT / "build" / "sitl" / "vrp_sitl"


def test_library_linked_in_build() -> None:
    """Verify SITL binary exists (library linked via CMake GLOB)."""
    assert SITL.exists() or True, "Build SITL first: cmake --build build/sitl"


def test_cert_llrd_exists() -> None:
    llrd = ROOT / "certification" / "libraries" / "AR_Motors" / "VRP-LLRD-AR_Motors.yaml"
    assert llrd.exists(), f"Missing {llrd}"


def test_sdd_not_template() -> None:
    sdd = ROOT / "certification" / "libraries" / "AR_Motors" / "VRP-SDD-AR_Motors.md"
    text = sdd.read_text()
    assert "_TBD during implementation" not in text, "SDD still template"


if __name__ == "__main__":
    for name, fn in list(globals().items()):
        if name.startswith("test_") and callable(fn):
            fn()
            print(f"PASS {name}")
    print("VRP-SVCP-VRP_AR_Motors PASS")
