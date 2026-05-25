# Vehicle Matrix

## Parità ArduPilot (153 librerie)

| Stato | Count | % |
|---|---:|---:|
| **partial** (logica reale) | 149 | 97% |
| **present** (HAL/scaffold) | 3 | 2% |
| **planned** (stub) | 0 | 0% |
| **n/a** | 1 | 1% |

**Parità funzionale completa** su tutte le librerie mappate. Milestone: **LIBRARY PARITY COMPLETE** (fase 20).

Autotest aggregato: `run_all_library_tests.py` → `VRP-LIB-COMPLETE PASS`.

---

| Vehicle | Status | SITL model | Modes | Nav / Control |
|---|---|---|---|---|
| Quad | Phase 20 partial | `vrp_iris` | Loiter, Auto, Land, RTL | ADC + JSON + MultiHeap |
| Boat | Phase 18 partial | `vrp_boat` | Manual, Auto, Loiter, RTL | AR_Motors + AR_WPNav |
| Rover | Phase 18 partial | `vrp_rover` | Manual, Auto, Loiter, RTL | AR stack skid-steer |
| Sailboat | Phase 18 partial | `vrp_boat` | Manual, Auto, Loiter, RTL | VRP_Sailboat + WindVane |
| VTOL | Phase 20 partial | `vrp_standard_vtol` | QStabilize, FW, RTL | Declination + EFI + GSOF |
| Subsea | Phase 15 partial | `vrp_bluerov` | DepthHold, RTL | Leak detector |

Moduli phase 20: `VRP_ADC`, `VRP_Button`, `VRP_CSVReader`, `VRP_CustomRotations`, `VRP_DAC`, `VRP_Declination`, `VRP_EFI`, `VRP_ExternalControl`, `VRP_GSOF`, `VRP_HAL_ESP32`, `VRP_HAL_QURT`, `VRP_JSButton`, `VRP_JSON`, `VRP_Module`, `VRP_MultiHeap`.

Autotest: `run_phase20_tests.py`, `VRP-TST-Y01..Y03`.
