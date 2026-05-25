#!/bin/zsh
set -euo pipefail

vehicle="${1:-quad}"
model="vrp_iris"
if [[ "${vehicle}" == "boat" ]]; then
  model="vrp_boat"
fi

cmake -S . -B build/sitl -DVRP_BOARD=sitl -DVRP_VEHICLE="${vehicle}"
cmake --build build/sitl
./build/sitl/vrp_sitl --vehicle "${vehicle}" --model "${model}" --once
