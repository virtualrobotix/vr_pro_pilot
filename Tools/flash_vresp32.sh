#!/bin/zsh
set -euo pipefail

board="${1:-VREsp32-v1}"
vehicle="${2:-quad}"

echo "Flashing placeholder for board=${board} vehicle=${vehicle}"
echo "Use esptool.py with ESP-IDF build artifacts for ${board}."
echo "APJ board ID: AP_HW_VRESP32_V1 (USB product 0x1851)"
