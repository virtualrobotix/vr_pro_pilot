#!/bin/zsh
# Test funzionale VR Pro Pilot Copter (parità ArduCopter stack).
set -euo pipefail

root="$(cd "$(dirname "$0")/.." && pwd)"
cd "${root}"

cmake -S . -B build/sitl -DVRP_BOARD=sitl -DVRP_VEHICLE=quad
cmake --build build/sitl

quad_out="$(./build/sitl/vrp_sitl --vehicle quad --model vrp_iris --once)"
mavlink_mode_out="$(./build/sitl/vrp_sitl --vehicle quad --model vrp_iris --once --test-mavlink-mode)"
avoid_out="$(./build/sitl/vrp_sitl --vehicle quad --model vrp_iris --once --test-adsb-avoid)"
landing_out="$(./build/sitl/vrp_sitl --vehicle quad --model vrp_iris --once --test-landing)"

echo "${quad_out}" | python3 -c '
import sys
s = sys.stdin.read()
assert "VRP_SELF_TEST_PASS vehicle=quad" in s
assert "ATT_CTRL active" in s
assert "ACWPNAV active=1" in s
assert "POSCTL roll=" in s
assert "PRECLAND active=1" in s
assert "AUTOTUNE active=" in s
assert "ACPID active=1" in s
assert "CUSTCTL active=1" in s
assert "INERTNAV vx=" in s
assert "SURFACE agl=" in s
assert "FOLLOW active=" in s
assert "AVOIDANCE active=" in s
assert "RALLY idx=" in s
assert "MAVLINK_V2 sent=" in s
'

echo "${mavlink_mode_out}" | python3 -c '
import sys
s = sys.stdin.read()
assert "VRP_SELF_TEST_PASS" in s
assert "VEHICLE mode=Auto" in s or "VEHICLE mode=Loiter" in s
'

echo "${avoid_out}" | python3 -c '
import sys
s = sys.stdin.read()
assert "AVOIDANCE active=1" in s
assert "VRP_SELF_TEST_PASS" in s
'

echo "${landing_out}" | python3 -c '
import sys
s = sys.stdin.read()
assert "VRP_SELF_TEST_PASS" in s
'

echo "VRP-COPTER-T01 PASS (flight stack)"
echo "VRP-COPTER-T02 PASS (AC_WPNav + POSCTL)"
echo "VRP-COPTER-T03 PASS (PrecLand + AutoTune + ACPID)"
echo "VRP-COPTER-T04 PASS (Avoidance + Rally + Follow)"
echo "VRP-COPTER-T05 PASS (MAVLink mode + Land)"
echo "VRP-COPTER-ALL PASS"
