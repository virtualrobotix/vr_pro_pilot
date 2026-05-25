# VREsp32 Board Support

| Board | APJ Board ID | USB Product | MCU | Status |
|---|---|---|---|---|
| VREsp32-v1 | AP_HW_VRESP32_V1 | 0x1851 | ESP32 | hwdef + HAL_ESP32 scaffold |

## Peripherals (VREsp32-v1)

- IMU: MPU6000
- Baro: BMP280
- Compass: QMC5883L
- Storage: SPI flash (4 MB)
- WiFi: enabled (AP+STA, sim in host build)

## Build

Host shape check (same vehicle stack as SITL, HAL simulato):

```bash
cmake -S . -B build/vresp32-v1 -DVRP_BOARD=VREsp32-v1 -DVRP_VEHICLE=quad -DVRP_TARGET_ESP32=ON
cmake --build build/vresp32-v1
./build/vresp32-v1/vrp_sitl --vehicle quad --once --esp32
```

SITL con backend ESP32 simulato (senza cross-compile):

```bash
./build/sitl/vrp_sitl --vehicle quad --once --esp32
```

## Flash

```bash
./Tools/flash_vresp32.sh VREsp32-v1 quad
```

## Common requirements

- USB vendor `0x27AC` (Laser Navigation / Virtual Robotix).
- ESP-IDF SDK placeholder in `modules/ESP-IDF/`.
- Same flight stack as VRBrain: SafetyCore → NavCore → VehicleCore → ControlCore.

## Smoke test

Vedi [`HW_V1_SMOKE_TEST_VRESP32.md`](HW_V1_SMOKE_TEST_VRESP32.md).
