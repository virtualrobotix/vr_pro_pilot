#!/bin/zsh
# Certification artifact verification gate.
set -euo pipefail

root="$(cd "$(dirname "$0")/.." && pwd)"
cd "${root}"

echo "== Regenerate cert artifacts =="
python3 Tools/cert/gen_parity_and_libraries.py
python3 Tools/cert/gen_cert_complete.py
python3 Tools/cert/gen_traceability.py

echo "== Verify counts =="
python3 - <<'PY'
import json
from pathlib import Path
reg = json.load(open("certification/LIBRARY_REGISTRY.json"))
assert len(reg) == 153, len(reg)
wired = sum(1 for f in Path("certification/libraries").glob("*/VRP-LLRD-*.yaml")
            if "status: wired" in f.read_text() or "wired: true" in f.read_text())
print(f"Libraries: {len(reg)}, wired: {wired}")
assert wired >= 20
PY

echo "== Verify no SDD templates =="
if rg -l "_TBD during implementation" certification/libraries --glob 'VRP-SDD-*.md' 2>/dev/null; then
  echo "ERROR: SDD templates remain"
  exit 1
fi

echo "== Verify HLRD + SRS =="
test -f certification/requirements/VRP-HLRD-003.yaml
test -f certification/requirements/VRP-SRS-001.md
test -f certification/modules/CopterCore/VRP-MLRD-CopterCore.yaml
test -f certification/VRP-CERT-STATUS.md

echo "== SVCP smoke (sample wired libs) =="
for lib in VRP_AC_AttitudeControl VRP_Landing VRP_AC_WPNav; do
  python3 "test/libraries/${lib}/test_api.py"
done

echo "== Copter SITL cert gate =="
./Tools/run_copter_sitl_tests.sh

echo "VRP-CERT-CHECKS PASS"
