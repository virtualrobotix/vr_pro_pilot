cmake_minimum_required(VERSION 3.20)
project(VRPilotPro LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(VRP_TARGET_CHIBIOS "Build chibios target artifacts" OFF)
option(VRP_TARGET_ESP32 "Build ESP32 target artifacts" OFF)
set(VRP_BOARD "sitl" CACHE STRING "Board target")
set(VRP_VEHICLE "quad" CACHE STRING "Default vehicle")

add_compile_definitions(VRP_BOARD="${VRP_BOARD}" VRP_VEHICLE="${VRP_VEHICLE}")
if(VRP_TARGET_CHIBIOS)
  add_compile_definitions(VRP_TARGET_CHIBIOS=1)
  if(VRP_BOARD STREQUAL "VRBrain-v54")
    add_compile_definitions(VRP_BOARD_V54=1)
  endif()
endif()
if(VRP_TARGET_ESP32)
  add_compile_definitions(VRP_TARGET_ESP32=1)
  if(VRP_BOARD STREQUAL "VREsp32-v1")
    add_compile_definitions(VRP_BOARD_VRESP32_V1=1)
  endif()
endif()

add_library(vrp_core
  src/hal/sitl/HAL_SITL.cpp
  src/hal/chibios/HAL_ChibiOS.cpp
  src/hal/esp32/HAL_ESP32.cpp
  src/middleware/uorb/UORB.cpp
  src/middleware/params/VRP_Param.cpp
  src/middleware/scheduler/Scheduler.cpp
  src/modules/mavlink/Heartbeat.cpp
  src/modules/mavlink/MavlinkCodec.cpp
  src/modules/mavlink/MavlinkMode.cpp
  src/modules/mavlink/MavlinkUdp.cpp
  src/modules/mavlink/MavlinkParser.cpp
  src/modules/mavlink/MavlinkUdpRx.cpp
  src/modules/ekf2/EKF2.cpp
  src/modules/control_allocator/ControlAllocator.cpp
  src/modules/control_core/ControlCore.cpp
  src/modules/vehicle_core/VehicleCore.cpp
  src/modules/nav_core/NavCore.cpp
  src/modules/safety_core/SafetyCore.cpp
  src/modules/sensor_core/SensorCore.cpp
  src/modules/simulation/FDM.cpp
  src/modules/uxrce_dds_client/DdsBridge.cpp
  src/modules/uxrce_dds_client/UxrceSession.cpp
  src/modules/library_core/LibraryCore.cpp
  src/vehicles/VRP_Vehicle.cpp
  src/vehicles/quad/Quad.cpp
  src/vehicles/boat/Boat.cpp
  src/vehicles/rover/Rover.cpp
  src/vehicles/sailboat/Sailboat.cpp
  src/vehicles/vtol/VTOL.cpp
  src/vehicles/subsea/Subsea.cpp
)

file(GLOB_RECURSE VRP_LIBRARY_SOURCES CONFIGURE_DEPENDS src/libraries/*/*.cpp)
target_sources(vrp_core PRIVATE ${VRP_LIBRARY_SOURCES})
target_include_directories(vrp_core PUBLIC src)

add_executable(vrp_sitl src/main.cpp)
target_link_libraries(vrp_sitl PRIVATE vrp_core)

enable_testing()
add_test(NAME vrp_self_test_quad COMMAND vrp_sitl --vehicle quad --model vrp_iris --once)
add_test(NAME vrp_self_test_boat COMMAND vrp_sitl --vehicle boat --model vrp_boat --once)
add_test(NAME vrp_self_test_rover COMMAND vrp_sitl --vehicle rover --model vrp_rover --once)
add_test(NAME vrp_self_test_sailboat COMMAND vrp_sitl --vehicle sailboat --model vrp_boat --once)
