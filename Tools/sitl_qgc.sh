#!/bin/zsh
# Avvia VR Pro Pilot SITL in modalità GCS (loop continuo, MAVLink UDP standard QGC).
# In QGroundControl: Comm Links → UDP → porta 14550 (default) → Connect.
set -euo pipefail

root="$(cd "$(dirname "$0")/.." && pwd)"
cd "${root}"

vehicle="${1:-boat}"
home="${2:-calcio}"

model="vrp_iris"
case "${vehicle}" in
  boat|sailboat) model="vrp_boat" ;;
  rover) model="vrp_rover" ;;
  vtol) model="vrp_standard_vtol" ;;
  subsea) model="vrp_bluerov" ;;
esac

cmake -S . -B build/sitl -DVRP_BOARD=sitl -DVRP_VEHICLE="${vehicle}"
cmake --build build/sitl

exec ./build/sitl/vrp_sitl --vehicle "${vehicle}" --model "${model}" --gcs --home "${home}"
