#!/bin/zsh
# Avvia VR Pro Pilot SITL in modalità GCS (loop continuo, MAVLink UDP standard QGC).
# In QGroundControl: Comm Links → UDP → porta 14550 (default) → Connect.
set -euo pipefail

root="$(cd "$(dirname "$0")/.." && pwd)"
cd "${root}"

vehicle="${1:-quad}"
home="${2:-calcio}"

cmake -S . -B build/sitl -DVRP_BOARD=sitl -DVRP_VEHICLE="${vehicle}"
cmake --build build/sitl

exec ./build/sitl/vrp_sitl --vehicle "${vehicle}" --model vrp_iris --gcs --home "${home}"
