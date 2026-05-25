SHELL := /bin/zsh

.PHONY: sitl_quad sitl_boat chibios_vrbrain_v54_quad chibios_vrbrain_v54_boat esp32_vresp32_v1_quad esp32_vresp32_v1_boat gen_hwdef test_sitl

sitl_quad:
	cmake -S . -B build/sitl -DVRP_BOARD=sitl -DVRP_VEHICLE=quad
	cmake --build build/sitl
	./build/sitl/vrp_sitl --vehicle quad --model vrp_iris --once

sitl_boat:
	cmake -S . -B build/sitl -DVRP_BOARD=sitl -DVRP_VEHICLE=boat
	cmake --build build/sitl
	./build/sitl/vrp_sitl --vehicle boat --model vrp_boat --once

chibios_vrbrain_v54_quad:
	cmake -S . -B build/vrbrain-v54-quad -DVRP_BOARD=VRBrain-v54 -DVRP_VEHICLE=quad -DVRP_TARGET_CHIBIOS=ON
	cmake --build build/vrbrain-v54-quad

chibios_vrbrain_v54_boat:
	cmake -S . -B build/vrbrain-v54-boat -DVRP_BOARD=VRBrain-v54 -DVRP_VEHICLE=boat -DVRP_TARGET_CHIBIOS=ON
	cmake --build build/vrbrain-v54-boat

esp32_vresp32_v1_quad:
	cmake -S . -B build/vresp32-v1-quad -DVRP_BOARD=VREsp32-v1 -DVRP_VEHICLE=quad -DVRP_TARGET_ESP32=ON
	cmake --build build/vresp32-v1-quad
	./build/vresp32-v1-quad/vrp_sitl --vehicle quad --once --esp32

esp32_vresp32_v1_boat:
	cmake -S . -B build/vresp32-v1-boat -DVRP_BOARD=VREsp32-v1 -DVRP_VEHICLE=boat -DVRP_TARGET_ESP32=ON
	cmake --build build/vresp32-v1-boat

gen_hwdef:
	./Tools/gen_all_hwdef.sh

test_sitl:
	./Tools/run_sitl_tests.sh
