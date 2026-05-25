#!/usr/bin/env python3
"""SITL end-to-end: 5 waypoint mission around Calcio (5 km radius), GUIDED climb, AUTO nav, LAND."""

from __future__ import annotations

import re
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
BUILD_DIR = ROOT / "build" / "sitl"
EXE = BUILD_DIR / "vrp_sitl"

CALCIO_LAT = 45.5156000
CALCIO_LON = 9.8494000
WAYPOINT_BEARINGS = [0, 72, 144, 216, 288]


def build_sitl() -> None:
    subprocess.run(
        ["cmake", "-S", str(ROOT), "-B", str(BUILD_DIR), "-DVRP_BOARD=sitl", "-DVRP_VEHICLE=quad"],
        check=True,
    )
    subprocess.run(["cmake", "--build", str(BUILD_DIR)], check=True)


def run_mission() -> str:
    proc = subprocess.run(
        [str(EXE), "--vehicle", "quad", "--model", "vrp_iris", "--once", "--test-calcio-mission"],
        check=False,
        capture_output=True,
        text=True,
    )
    output = proc.stdout + proc.stderr
    if proc.returncode != 0:
        print(output)
        raise SystemExit(f"vrp_sitl exited with code {proc.returncode}")
    return output


def verify_log(output: str) -> None:
    checks = [
        ("mission upload 5 WP", "mission_upload count=5" in output),
        ("arm via MAVLink", "cmd=ARM" in output),
        ("GUIDED mode", "cmd=SET_MODE custom=4" in output),
        ("climb 100 m", "CALCIO_TEST climb_reached alt_m=" in output),
        ("AUTO waypoint nav", "cmd=SET_MODE custom=3" in output),
        ("WPNAV active", "WPNAV" in output and "dist=" in output),
        ("5 waypoint mission complete", "CALCIO_TEST mission_complete waypoints=5" in output),
        ("LAND mode", "cmd=SET_MODE custom=9" in output),
        ("landing complete", "CALCIO_TEST land_complete" in output),
        ("overall PASS", "CALCIO_TEST PASS waypoints=5" in output),
        ("SITL self-test", "VRP_SELF_TEST_PASS vehicle=quad" in output),
    ]

    print("\n=== Verifica log missione Calcio SITL ===\n")
    failed = []
    for name, ok in checks:
        status = "PASS" if ok else "FAIL"
        print(f"  [{status}] {name}")
        if not ok:
            failed.append(name)

    reached = re.findall(r"MISSION_TX reached=(\d+)", output)
    if reached:
        print(f"\n  Waypoint raggiunti (log): {', '.join(reached)}")

    gps_hits = re.findall(r"GPS lat=([0-9.]+) lon=([0-9.]+)", output)
    if gps_hits:
        last_lat, last_lon = gps_hits[-1]
        print(f"\n  Ultima posizione GPS: lat={last_lat} lon={last_lon}")
        print(f"  Home Calcio attesa:   lat={CALCIO_LAT} lon={CALCIO_LON}")

    if failed:
        print(f"\nVerifica FALLITA: {', '.join(failed)}")
        raise SystemExit(1)

    print("\nVerifica COMPLETATA: missione Calcio eseguita correttamente in SITL.\n")


def main() -> int:
    print("Building SITL quad...")
    build_sitl()
    print("Running Calcio mission scenario...")
    output = run_mission()
    verify_log(output)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
