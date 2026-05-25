#!/bin/zsh
# Shortcut: rover/boat/sailboat SITL visibile in QGroundControl (UDP 14550).
set -euo pipefail
root="$(cd "$(dirname "$0")/.." && pwd)"
exec "${root}/Tools/sitl_qgc.sh" "${1:-boat}" "${2:-calcio}"
