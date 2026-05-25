#!/bin/zsh
set -euo pipefail

root="$(cd "$(dirname "$0")/.." && pwd)"
cd "${root}"

gen() {
  local board="$1"
  local hal="$2"
  python3 Tools/vrp_hwdef_parser.py \
    --input "boards/${board}/hwdef.vrp" \
    --output "src/hal/${hal}/hwdef/${board}.h"
}

for board in VRBrain-v51 VRBrain-v52 VRBrain-v54 VRCore-v10 VRUBrain-v51; do
  gen "${board}" chibios
done

gen VREsp32-v1 esp32

echo "All hwdef headers generated."
