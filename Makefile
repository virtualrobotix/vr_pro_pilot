SHELL := /bin/zsh

.PHONY: sitl_quad sitl_boat chibios_vrbrain_v54_quad chibios_vrbrain_v54_boat test_sitl

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

test_sitl:
	./Tools/run_sitl_tests.sh
