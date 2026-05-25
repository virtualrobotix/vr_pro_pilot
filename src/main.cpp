#include <algorithm>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>

#include "hal/chibios/HAL_ChibiOS.h"
#include "hal/sitl/HAL_SITL.h"
#include "libraries/VRP_CANManager/VRP_CANManager.h"
#include "libraries/VRP_CRSF/VRP_CRSF.h"
#include "libraries/VRP_Common/VRP_Common.h"
#include "libraries/VRP_DroneCAN/VRP_DroneCAN.h"
#include "libraries/VRP_GCS_MAVLink/VRP_GCS_MAVLink.h"
#include "libraries/VRP_Frsky_Telem/VRP_Frsky_Telem.h"
#include "libraries/VRP_FlashIface/VRP_FlashIface.h"
#include "libraries/VRP_FlashStorage/VRP_FlashStorage.h"
#include "libraries/VRP_Hott_Telem/VRP_Hott_Telem.h"
#include "libraries/VRP_Landing/VRP_Landing.h"
#include "libraries/VRP_LTM_Telem/VRP_LTM_Telem.h"
#include "libraries/VRP_MSP/VRP_MSP.h"
#include "libraries/VRP_SRV_Channel/VRP_SRV_Channel.h"
#include "middleware/params/VRP_Param.h"
#include "middleware/uorb/UORB.h"
#include "modules/control_core/ControlCore.h"
#include "modules/mavlink/Heartbeat.h"
#include "modules/mavlink/MavlinkCodec.h"
#include "modules/library_core/LibraryCore.h"
#include "modules/nav_core/NavCore.h"
#include "modules/safety_core/SafetyCore.h"
#include "modules/simulation/FDM.h"
#include "modules/uxrce_dds_client/DdsBridge.h"
#include "modules/uxrce_dds_client/UxrceSession.h"
#include "modules/vehicle_core/VehicleCore.h"
#include "vehicles/VRP_Vehicle.h"

namespace {
std::string get_arg(const std::vector<std::string> &args, const std::string &key, const std::string &fallback) {
  for (size_t i = 0; i + 1 < args.size(); ++i) {
    if (args[i] == key) {
      return args[i + 1];
    }
  }
  return fallback;
}

bool has_flag(const std::vector<std::string> &args, const std::string &flag) {
  return std::find(args.begin(), args.end(), flag) != args.end();
}

void apply_param_mavlink(vrp::VRPParamStore &params, const vrp::MavlinkRxAction &rx, vrp::MavlinkTxBundle &tx) {
  if (rx.param_set) {
    params.set_by_name(rx.param_id, rx.param_value);
  }
  if (!rx.param_request && !rx.param_set) {
    return;
  }
  std::string key;
  if (rx.param_id[0] != '\0') {
    key = rx.param_id;
  } else if (rx.param_index < params.count()) {
    key = params.name_at(rx.param_index);
  }
  if (key.empty()) {
    return;
  }
  tx.send_param_value = true;
  std::strncpy(tx.param_id, key.c_str(), 16);
  tx.param_id[16] = '\0';
  tx.param_value = static_cast<float>(params.get(key, 0.0));
  uint16_t idx = 0;
  if (params.find_index(key, idx)) {
    tx.param_index = idx;
  }
  tx.param_count = static_cast<uint16_t>(params.count());
}
} // namespace

int main(int argc, char **argv) {
  std::vector<std::string> args(argv + 1, argv + argc);
  const std::string vehicle_kind = get_arg(args, "--vehicle", "quad");
  const std::string model = get_arg(args, "--model", "vrp_iris");
  const bool once = has_flag(args, "--once");
  const bool chibios = has_flag(args, "--chibios");
  const bool test_mavlink_rx = has_flag(args, "--test-mavlink-rx");
  const bool test_mavlink_mode = has_flag(args, "--test-mavlink-mode");
  const bool test_mavlink_mission = has_flag(args, "--test-mavlink-mission");
  const bool test_mavlink_upload = has_flag(args, "--test-mavlink-upload");
  const bool test_failsafe = has_flag(args, "--test-failsafe");
  const bool test_landing = has_flag(args, "--test-landing");
  const bool test_mavlink_param = has_flag(args, "--test-mavlink-param");
  const bool enable_dds = has_flag(args, "--enable-dds");
  const bool enable_uxrce = has_flag(args, "--enable-uxrce");
  const bool test_adsb_avoid = has_flag(args, "--test-adsb-avoid");
  const bool test_flash = has_flag(args, "--test-flash");

  vrp::HALSITL hal_sitl;
  vrp::HALChibiOS hal_chibios;
  vrp::IHAL &hal = chibios ? static_cast<vrp::IHAL &>(hal_chibios) : static_cast<vrp::IHAL &>(hal_sitl);
  hal.init();

  vrp::UORB uorb;
  vrp::VRPParamStore params;
  params.seed_defaults();
  auto vehicle = vrp::make_vehicle(vehicle_kind, uorb, params);
  vrp::FDM fdm(model);
  vrp::FDMState fdm_state;
  vrp::SafetyCore safety;
  vrp::NavCore nav_core;
  vrp::VehicleCore vehicle_core;
  vrp::ControlCore control;
  vrp::VRP_GCS_MAVLink mavlink;
  vrp::VRP_CANManager can_mgr;
  vrp::VRP_DroneCAN dronecan;
  vrp::VRP_SRV_Channel srv;
  vrp::VRP_Frsky_Telem frsky;
  vrp::VRP_MSP msp;
  vrp::VRP_Hott_Telem hott;
  vrp::VRP_CRSF crsf;
  vrp::VRP_LTM_Telem ltm;
  vrp::VRP_FlashIface flash_iface;
  vrp::VRP_FlashStorage flash_store;
  vrp::DdsBridge dds;
  vrp::UxrceSession uxrce;
  vrp::LibraryCore library_core;
  vehicle->setup();
  flash_store.init(flash_iface);
  flash_store.load(params);
  safety.init(vehicle_kind, params);
  if (test_adsb_avoid) {
    safety.configure_adsb_test(25.0);
  }
  nav_core.init(vehicle_kind, params.get("nav.cruise_speed", 2.0));
  vehicle_core.init(vehicle_kind, params);
  control.init(vehicle_kind, params);
  mavlink.init();
  can_mgr.init();
  dronecan.init(127);
  srv.init();
  frsky.init();
  msp.init();
  hott.init();
  crsf.init();
  ltm.init();
  if (enable_dds) {
    dds.init();
  }
  if (enable_uxrce) {
    uxrce.init(8888);
  }
  library_core.init();

  if (test_mavlink_rx) {
    params.set("system.auto_arm_sitl", 0.0);
    safety.init(vehicle_kind, params);
  }
  if (test_failsafe) {
    params.set("failsafe.test_force_rtl", 1.0);
    params.set("system.auto_arm_sitl", 1.0);
    safety.init(vehicle_kind, params);
  }

  const uint32_t iterations = once ? (test_landing ? 10U : 5U) : 25;
  constexpr double kDtS = 0.02;
  bool gcs_link = false;
  for (uint32_t i = 0; i < iterations; ++i) {
    hal.run_once([&]() {
      const uint64_t tick = i + 1;
      vehicle->scheduler().run(hal.now_ms());
      vehicle->loop();
      fdm.step(vehicle_kind, kDtS, fdm_state);
      safety.update(kDtS, hal.now_ms(), fdm_state, uorb);

      vrp::MavlinkRxAction rx_action{};
      std::string rx_line = mavlink.poll(rx_action);
      bool mavlink_rx_active = rx_line.find("idle") == std::string::npos;
      if (test_mavlink_rx && i == 1) {
        uint8_t seq = 0;
        const auto arm_frame = vrp::MavlinkCodec::command_long(1, 1, 400, 1.0F, seq);
        mavlink.inject_frame_for_test(arm_frame, rx_action);
        rx_line = "MAVLINK_RX msg=76 cmd=ARM";
      }
      if (test_mavlink_mode && i == 2) {
        uint8_t seq = 0;
        const uint32_t custom = (vehicle_kind == "vtol") ? 19U : (vehicle_kind == "boat") ? 10U : 3U;
        const auto mode_frame = vrp::MavlinkCodec::set_mode(1, 1, 0x01, custom, seq);
        mavlink.inject_frame_for_test(mode_frame, rx_action);
        rx_line = "MAVLINK_RX msg=11 cmd=SET_MODE custom=" + std::to_string(custom);
      }
      if (test_landing && i == 2) {
        uint8_t seq = 0;
        const auto land_frame = vrp::MavlinkCodec::set_mode(1, 1, 0x01, 9U, seq);
        mavlink.inject_frame_for_test(land_frame, rx_action);
        rx_line = "MAVLINK_RX msg=11 cmd=SET_MODE custom=9";
        mavlink_rx_active = true;
      }
      if (test_mavlink_mission && i == 2) {
        uint8_t seq = 0;
        const auto list_frame = vrp::MavlinkCodec::mission_request_list(1, 1, seq);
        mavlink.inject_frame_for_test(list_frame, rx_action);
        rx_line = "MAVLINK_RX msg=43 mission_req_list";
      }
      if (test_mavlink_mission && i == 3) {
        uint8_t seq = 0;
        const auto item_frame = vrp::MavlinkCodec::mission_request_int(1, 1, 0, seq);
        mavlink.inject_frame_for_test(item_frame, rx_action);
        rx_line = "MAVLINK_RX msg=51 mission_req_item seq=0";
        mavlink_rx_active = true;
      }
      if (test_mavlink_upload && i == 1) {
        uint8_t seq = 0;
        const auto count_frame = vrp::MavlinkCodec::mission_count(1, 1, 2, 0, seq);
        mavlink.inject_frame_for_test(count_frame, rx_action);
        rx_line = "MAVLINK_RX msg=44 mission_upload count=2";
        mavlink_rx_active = true;
      }
      if (test_mavlink_upload && i == 2) {
        uint8_t seq = 0;
        const auto item0 = vrp::MavlinkCodec::mission_item_int(1, 1, 0, 3, 450001000, 90001000, 10.0F, seq);
        mavlink.inject_frame_for_test(item0, rx_action);
        rx_line = "MAVLINK_RX msg=73 mission_upload item=0";
        mavlink_rx_active = true;
      }
      if (test_mavlink_upload && i == 3) {
        uint8_t seq = 0;
        const auto item1 = vrp::MavlinkCodec::mission_item_int(1, 1, 1, 3, 450002000, 90002000, 12.0F, seq);
        mavlink.inject_frame_for_test(item1, rx_action);
        rx_line = "MAVLINK_RX msg=73 mission_upload item=1";
        mavlink_rx_active = true;
      }
      if (test_mavlink_param && i == 2) {
        uint8_t seq = 0;
        const auto param_req = vrp::MavlinkCodec::param_request_read(1, 1, 0, "NAV_SPEED", seq);
        mavlink.inject_frame_for_test(param_req, rx_action);
        rx_line = "MAVLINK_RX msg=20 param_req id=NAV_SPEED";
        mavlink_rx_active = true;
      }
      if (test_mavlink_param && i == 3) {
        uint8_t seq = 0;
        const auto set_frame = vrp::MavlinkCodec::param_set(1, 1, "NAV_SPEED", 3.5F, seq);
        mavlink.inject_frame_for_test(set_frame, rx_action);
        rx_line = "MAVLINK_RX msg=23 param_set id=NAV_SPEED val=3.5";
        mavlink_rx_active = true;
      }
      if (mavlink_rx_active) {
        safety.note_gcs_link(tick);
        gcs_link = true;
      }
      safety.apply_mavlink_action(rx_action);
      if (rx_action.param_set) {
        flash_store.save(params);
      }
      if (test_flash && i == 2) {
        params.set("NAV_SPEED", 4.2);
        flash_store.save(params);
      }
      vehicle_core.apply_mavlink(rx_action);

      const bool rtl_nav = safety.rtl_nav_active();
      const bool nav_active = rtl_nav ||
                              (safety.mission_active() &&
                               (vehicle_core.mode() == "Auto" || vehicle_core.mode() == "FW" ||
                                safety.flight_mode() == "Auto" || safety.flight_mode() == "RTL"));
      const bool use_l1 =
          vehicle_kind == "vtol" &&
          (vehicle_core.vtol_phase() == "FW" || vehicle_core.mode() == "FW" || tick >= 5);
      const vrp::WpNavOutput nav =
          nav_core.update(safety.position(), safety.nav_target(), safety.mission_prev_target(), use_l1, nav_active,
                          uorb);

      vehicle_core.update(tick, safety.is_armed(), safety.flight_mode(), safety.position(), safety.battery(), nav,
                          safety.rangefinder(), gcs_link, uorb);
      const auto &sp = vehicle_core.setpoints();
      const std::string &mode = vehicle_core.mode();

      float throttle = 0.0F;
      vrp::ServoOutput servos{};
      if (vehicle_kind == "quad") {
        const auto motors =
            control.update_quad(safety.is_armed(), safety.fence_breached(), safety.attitude(), safety.position(), sp,
                                kDtS, uorb);
        throttle = (motors.m1 + motors.m2 + motors.m3 + motors.m4) / 4.0F;
        servos = srv.map_quad(motors);
      } else if (vehicle_kind == "boat") {
        const auto boat =
            control.update_boat(safety.is_armed(), safety.fence_breached(), safety.position(), sp, kDtS, uorb);
        throttle = boat.left;
        servos = srv.map_boat(boat);
      } else if (vehicle_kind == "vtol") {
        const auto motors =
            control.update_vtol(safety.is_armed(), safety.fence_breached(), safety.attitude(), safety.position(), sp,
                                safety.airspeed().speed_m_s, kDtS, uorb);
        throttle = (motors.m1 + motors.m2 + motors.m3 + motors.m4) / 4.0F;
        servos = srv.map_vtol(motors, vehicle_core.vtol_phase());
      } else if (vehicle_kind == "subsea") {
        const auto sub = control.update_subsea(safety.is_armed(), safety.fence_breached(), sp, uorb);
        throttle = sub.left;
        servos = srv.map_boat(sub);
      }
      uorb.publish("actuators/srv", format_servos(servos));

      const auto hb = vrp::Heartbeat::build(vehicle_kind, mode, hal.now_ms(), safety.is_armed());
      uorb.publish("mavlink/heartbeat", hb);
      const uint16_t mission_seq =
          safety.mission_active() ? static_cast<uint16_t>(safety.mission_index()) : static_cast<uint16_t>(0xFFFF);
      vrp::MavlinkTxBundle tx_bundle{};
      tx_bundle.mission = safety.build_mission_tx(rx_action);
      const int reached_idx = safety.consume_mission_item_reached();
      if (reached_idx >= 0) {
        tx_bundle.mission.send_item_reached = true;
        tx_bundle.mission.reached_seq = static_cast<uint16_t>(reached_idx);
      }
      apply_param_mavlink(params, rx_action, tx_bundle);
      if (test_mavlink_param && i == 2) {
        tx_bundle.send_home_position = true;
        tx_bundle.home_lat_e7 = static_cast<int32_t>(safety.gps().lat_deg * 1e7);
        tx_bundle.home_lon_e7 = static_cast<int32_t>(safety.gps().lon_deg * 1e7);
        tx_bundle.home_alt_mm = static_cast<int32_t>(safety.gps().alt_m * 1000.0);
      }
      const std::string mavlink_v2 =
          mavlink.transmit(safety.is_armed(), mode, safety.attitude(), safety.gps(), safety.battery(), hal.now_ms(),
                           mission_seq, &tx_bundle);
      if (tx_bundle.mission.send_upload_ack) {
        safety.clear_mission_upload_ack();
      }
      const std::string dronecan_hb = dronecan.heartbeat(hal.now_ms());
      const std::string dronecan_esc = dronecan.esc_status(hal.now_ms(), throttle);
      const std::string dronecan_can = dronecan.publish_esc(can_mgr, throttle);
      uorb.publish("dronecan/heartbeat", dronecan_hb);
      uorb.publish("dronecan/esc", dronecan_esc);

      std::cout << hb << "\n";
      std::cout << vrp::Heartbeat::build_attitude(safety.attitude(), hal.now_ms()) << "\n";
      std::cout << mavlink_v2 << "\n";
      std::cout << mavlink.last_mission_tx_summary() << "\n";
      std::cout << rx_line << "\n";
      std::cout << "SENSORS " << safety.sensors_summary() << "\n";
      std::cout << format_rc(vehicle_core.rc()) << "\n";
      std::cout << vehicle_core.osd_line() << "\n";
      std::cout << vehicle_core.script_line() << "\n";
      std::cout << safety.mission_status() << "\n";
      std::cout << safety.failsafe_summary() << "\n";
      std::cout << safety.smart_rtl_summary() << "\n";
      std::cout << format_wpnav(nav) << "\n";
      if (nav_core.last_l1().valid) {
        std::cout << format_l1(nav_core.last_l1()) << "\n";
      }
      std::cout << format_servos(servos) << "\n";
      if (vehicle_kind == "vtol") {
        if (const auto tecs = uorb.subscribe("control/tecs")) {
          std::cout << *tecs << "\n";
        }
        if (const auto apm = uorb.subscribe("control/apm")) {
          std::cout << *apm << "\n";
        }
      }
      std::cout << frsky.update(mode, safety.attitude(), safety.battery(), safety.position(), hal.now_ms()) << "\n";
      std::cout << msp.update(safety.attitude(), safety.position(), safety.battery(), hal.now_ms()) << "\n";
      std::cout << crsf.update(safety.attitude(), safety.battery(), vehicle_core.rssi(), hal.now_ms()) << "\n";
      std::cout << ltm.update(safety.position(), safety.gps(), hal.now_ms()) << "\n";
      std::cout << vehicle_core.rssi_line() << "\n";
      std::cout << vehicle_core.gear_line() << "\n";
      if (enable_dds) {
        uorb.publish("/vrp/in/vehicle_command", "cmd=hold");
        std::cout << dds.tick(hal.now_ms(), mode, safety.is_armed(), uorb) << "\n";
      }
      if (enable_uxrce) {
        std::cout << uxrce.tick(hal.now_ms(), uorb) << "\n";
      }
      std::cout << hott.update(safety.attitude(), safety.position(), safety.battery(), hal.now_ms()) << "\n";
      std::cout << safety.avoidance_summary() << "\n";
      std::cout << safety.stats_summary() << "\n";
      std::cout << safety.open_drone_id_line() << "\n";
      std::cout << flash_iface.summary() << "\n";
      std::cout << flash_store.status() << "\n";
      std::cout << library_core.tick(tick, safety.position(), safety.gps(), safety.attitude(), safety.rangefinder(),
                                     vehicle_core.rc(), vehicle_core.rssi(), safety.battery(), throttle,
                                     safety.is_armed(), mode, safety.flight_mode() == "RTL", gcs_link, hal.now_ms(),
                                     uorb)
                << "\n";
      if (mode == "Land") {
        std::cout << format_landing(vehicle_core.landing()) << "\n";
      }
      std::cout << "VEHICLE mode=" << mode;
      if (vehicle_kind == "vtol") {
        std::cout << " vtol_phase=" << vehicle_core.vtol_phase();
      }
      std::cout << "\n";
      std::cout << dronecan_hb << "\n";
      std::cout << dronecan_esc << "\n";
      std::cout << dronecan_can << "\n";
      std::cout << can_mgr.status() << "\n";
      std::cout << "SAFETY_CORE armed=" << (safety.is_armed() ? 1 : 0) << " mode=" << safety.flight_mode()
                << " pos_z=" << safety.position().z << " fence=" << (safety.fence_breached() ? 1 : 0) << "\n";
      if (vehicle_kind == "quad" || vehicle_kind == "vtol") {
        std::cout << "ATT_CTRL " << (safety.is_armed() && !safety.fence_breached() ? "active" : "idle") << "\n";
      }
      std::cout << safety.logger_summary() << "\n";
      std::cout << "SIM_STATE vehicle=" << vehicle_kind << " x=" << fdm_state.x << " y=" << fdm_state.y
                << " z=" << fdm_state.z << " yaw_deg=" << fdm_state.yaw_deg << "\n";
    });
    hal.sleep_ms(20);
  }

  mavlink.shutdown();
  if (chibios) {
    auto &hal_ch = static_cast<vrp::HALChibiOS &>(hal);
    std::cout << "BOARD " << hal_ch.board_info() << "\n";
    std::cout << hal_ch.flash_info() << "\n";
  }
  std::cout << "VRP_SELF_TEST_PASS vehicle=" << vehicle_kind << " hal=" << hal.name() << "\n";
  return 0;
}
