#include "modules/library_core/LibraryCore.h"

#include <sstream>

namespace vrp {

bool LibraryCore::init() {
  soaring_.init();
  rpm_.init();
  wind_.init();
  terrain_.init();
  rally_.init();
  ais_.init();
  surface_.init();
  beacon_.init();
  rc_telem_.init();
  esc_telem_.init();
  mount_.init();
  gripper_.init();
  parachute_.init();
  relay_.init();
  winch_.init();
  ibus_.init();
  devo_.init();
  servo_telem_.init();
  notify_.init();
  rtc_.init();
  camera_.init();
  networking_.init();
  generator_.init();
  vtx_.init();
  viso_.init();
  temp_.init();
  serial_.init();
  filesystem_.init();
  menu_.init();
  olc_.init();
  piccolo_.init();
  blheli_.init();
  nmea_.init();
  follow_.init();
  leak_.init();
  wheel_.init();
  quicktune_.init();
  tuning_.init();
  torqeedo_.init();
  romfs_.init();
  kde_can_.init();
  fettec_.init();
  radio_.init();
  sbus_out_.init();
  serial_led_.init();
  srv_evt_.init();
  rc_map_.init();
  storage_.init();
  temp_cal_.init();
  autotune_.init();
  precland_.init();
  volz_.init();
  robotis_.init();
  onvif_.init();
  irlock_.init();
  icengine_.init();
  ramtron_.init();
  lightware_.init();
  board_cfg_.init();
  autorot_.init();
  navigation_.init();
  inertial_nav_.init();
  ext_ahrs_.init();
  nav_ekf_.init();
  internal_err_.init();
  ar_motors_.init(ArFrameClass::Boat, true);
  ar_wpnav_.init(2.0, 2.0);
  hal_linux_.init();
  hal_empty_.init();
  cust_ctl_.init();
  input_mgr_.init();
  ac_pid_.init();
  sprayer_.init();
  ap_avoid_.init();
  dal_.init();
  gyro_fft_.init();
  fw_chk_.init();
  iomcu_.init();
  accel_cal_.init();
  adc_.init();
  button_.init();
  csv_.init();
  crot_.init();
  dac_.init();
  decl_.init();
  efi_.init();
  ext_ctl_.init();
  gsof_.init();
  hal_esp32_.init();
  hal_qurt_.init();
  jsbtn_.init();
  json_.init();
  module_.init();
  multi_heap_.init();
  have_prev_z_ = false;
  have_prev_xy_ = false;
  return true;
}

std::string LibraryCore::tick(uint64_t tick, const LocalPosition &pos, const GpsSample &gps, const Attitude &att,
                              const RangeFinderSample &rng, const RcChannels &rc, const RssiSample &rssi,
                              const BatteryStatus &battery, float throttle, bool armed, const std::string &mode,
                              bool rtl_active, bool gcs_link, uint64_t time_ms, UORB &uorb) {
  double climb = 0.0;
  double dx = 0.0;
  double dy = 0.0;
  if (have_prev_z_) {
    climb = (pos.z - prev_z_) / 0.02;
  }
  if (have_prev_xy_) {
    dx = pos.x - prev_x_;
    dy = pos.y - prev_y_;
  }
  prev_z_ = pos.z;
  prev_x_ = pos.x;
  prev_y_ = pos.y;
  have_prev_z_ = true;
  have_prev_xy_ = true;

  const auto soaring = soaring_.update(-pos.z, climb);
  const auto rpm = rpm_.update(throttle);
  const auto wind = wind_.update(tick);
  const auto terrain = terrain_.height_at(gps.lat_deg, gps.lon_deg);
  const auto rally = rally_.nearest(pos);
  const auto ais = ais_.update(tick, pos.x, pos.y);
  const auto surface = surface_.update(rng, att.pitch_rad);
  const auto beacon = beacon_.update(pos.x, pos.y);
  const auto esc = esc_telem_.update(throttle, static_cast<float>(battery.voltage_v), time_ms);
  const auto mount = mount_.update(att, armed);
  const float grip_cmd = (rc.yaw + 1.0F) * 0.5F;
  const auto grip = gripper_.update(grip_cmd, armed);
  parachute_.update(rtl_active, -pos.z);
  const auto relays = relay_.update(armed, tick);
  const auto winch = winch_.update(rc.throttle, armed);
  const auto servo = servo_telem_.update(throttle, static_cast<float>(battery.voltage_v), time_ms);
  const auto cam = camera_.update(armed, tick);
  const auto net = networking_.update(gcs_link, tick);
  const auto gen = generator_.update(throttle, armed);
  const auto vtx = vtx_.update(armed, tick);
  const auto viso = viso_.update(dx, dy, 0.02);
  const auto temp = temp_.update(throttle, tick);
  const auto ports = serial_.port_active_mask(tick);
  const auto fs = filesystem_.status(tick);
  const auto olc = olc_.update(armed, dx, dy);
  const auto piccolo = piccolo_.update(armed, tick);
  const auto blheli = blheli_.update(throttle, armed);
  const auto nmea = nmea_.update(gps, armed, tick);
  const auto follow = follow_.update(mode, 100.0, 0.0, pos.x, pos.y);
  const auto leak = leak_.update(armed, -pos.z, tick);
  const auto wheel = wheel_.update(dx, dy, armed);
  const auto quicktune = quicktune_.update(armed, rc.aux1, tick);
  const auto tuning = tuning_.update(rc, armed);
  const auto torqeedo = torqeedo_.update(throttle, armed, static_cast<float>(battery.voltage_v));
  const auto romfs = romfs_.status(tick);
  const auto kde = kde_can_.update(throttle, armed, tick);
  const auto fettec = fettec_.update(throttle, armed);
  const auto radio = radio_.update(rssi, armed);
  const auto sbus = sbus_out_.update(rc, armed, tick);
  const auto serled = serial_led_.update(armed, tick);
  const auto srv_evt = srv_evt_.update(armed, throttle, tick);
  const auto rcmap = rc_map_.map(rc);
  const auto storage = storage_.status(tick);
  const auto tempcal = temp_cal_.update(throttle, tick);
  const auto autotune = autotune_.update(armed, rc.aux1, tick);
  const auto precland = precland_.update(rng, armed, mode);
  const auto volz = volz_.update(rc.yaw, armed, tick);
  const auto robotis = robotis_.update(rc.pitch, throttle, armed);
  const auto onvif = onvif_.update(armed, gcs_link, tick);
  const auto irlock = irlock_.update(armed, pos.x, pos.y, tick);
  const auto icengine = icengine_.update(throttle, armed);
  const auto ramtron = ramtron_.status(tick);
  const auto lightware = lightware_.update(rng, armed);
  const auto board = board_cfg_.status(tick);
  const auto autorot = autorot_.update(armed, rtl_active || mode == "RTL", throttle);
  const auto nav = navigation_.update(mode, pos, 100.0, 0.0);
  const auto inav = inertial_nav_.update(pos, armed);
  const auto xahrs = ext_ahrs_.update(att, armed);
  const auto ekf = nav_ekf_.update(pos, armed, tick);
  const auto ierr = internal_err_.update(armed, tick);
  const auto armot = ar_motors_.update(throttle, rc.yaw, armed);
  const auto arwp = ar_wpnav_.update(pos, att, Waypoint{50.0, 0.0, 0.0}, Waypoint{}, mode,
                                      mode == "Auto" || mode == "Loiter" || mode == "RTL");
  const auto hallx = hal_linux_.status();
  const auto halempty = hal_empty_.status();
  const auto cust = cust_ctl_.update(armed, rc.roll, rc.pitch);
  const auto inputm = input_mgr_.update(rc, armed);
  const auto pid = ac_pid_.update(armed, rc.roll);
  const auto spray = sprayer_.update(armed, rc.aux2);
  const auto apavoid = ap_avoid_.update(armed, static_cast<float>(rng.distance_m));
  const auto dal = dal_.status();
  const auto fft = gyro_fft_.update(armed, static_cast<float>(att.roll_rad), tick);
  const auto fw = fw_chk_.verify(tick);
  const auto iomcu = iomcu_.status(armed, tick);
  const auto acccal = accel_cal_.update(armed, tick);
  const auto adc = adc_.update(battery, armed);
  const auto btn = button_.update(armed, rc.aux1);
  const auto csv = csv_.update(tick, armed);
  const auto crot = crot_.update(att, armed);
  const auto dac = dac_.update(throttle, armed);
  const auto decl = decl_.update(gps);
  const auto efi = efi_.update(throttle, armed, battery);
  const auto extctl = ext_ctl_.update(armed, gcs_link);
  const auto gsof = gsof_.update(gps);
  const auto halesp = hal_esp32_.status();
  const auto halqurt = hal_qurt_.status();
  const auto jsbtn = jsbtn_.update(rc, armed);
  const auto json = json_.update(tick, armed);
  const auto mod = module_.update(tick, armed);
  const auto mheap = multi_heap_.status();

  uorb.publish("aux/soaring", format_soaring(soaring));
  uorb.publish("aux/camera", format_camera(cam));
  uorb.publish("aux/network", format_network(net));
  uorb.publish("aux/generator", format_generator(gen));
  uorb.publish("aux/vtx", format_vtx(vtx));
  uorb.publish("aux/viso", format_visual_odom(viso));
  uorb.publish("aux/temp", format_temperature(temp));
  uorb.publish("aux/filesystem", format_filesystem(fs));
  uorb.publish("aux/olc", format_olc(olc));
  uorb.publish("aux/blheli", format_blheli(blheli));
  uorb.publish("aux/torqeedo", format_torqeedo(torqeedo));
  uorb.publish("aux/romfs", format_romfs(romfs));
  uorb.publish("aux/kdecan", format_kde_can(kde));
  uorb.publish("aux/radio", format_radio(radio));
  uorb.publish("aux/storage", format_storage_manager(storage));
  uorb.publish("aux/precland", format_prec_land(precland));
  uorb.publish("aux/irlock", format_irlock(irlock));
  uorb.publish("aux/board", format_board_config(board));
  uorb.publish("aux/navigation", format_navigation(nav));
  uorb.publish("aux/inertial_nav", format_inertial_nav(inav));

  std::ostringstream oss;
  oss << format_soaring(soaring) << "\n"
      << format_rpm(rpm) << "\n"
      << format_wind(wind) << "\n"
      << format_terrain(terrain) << "\n"
      << format_rally(rally) << "\n"
      << format_ais(ais) << "\n"
      << format_surface_distance(surface) << "\n"
      << format_beacon(beacon) << "\n"
      << rc_telem_.update(rc, rssi, time_ms) << "\n"
      << format_esc_telem(esc) << "\n"
      << format_mount(mount) << "\n"
      << format_gripper(grip) << "\n"
      << format_parachute(parachute_.deployed(), parachute_.deployed()) << "\n"
      << format_relay(relays) << "\n"
      << format_winch(winch) << "\n"
      << ibus_.update(att, battery, time_ms) << "\n"
      << devo_.update(pos, battery, time_ms) << "\n"
      << format_servo_telem(servo) << "\n"
      << notify_.update(armed, mode, tick) << "\n"
      << rtc_.update(time_ms) << "\n"
      << format_camera(cam) << "\n"
      << format_network(net) << "\n"
      << format_generator(gen) << "\n"
      << format_vtx(vtx) << "\n"
      << format_visual_odom(viso) << "\n"
      << format_temperature(temp) << "\n"
      << format_serial_ports(ports) << "\n"
      << format_filesystem(fs) << "\n"
      << menu_.update(tick, armed) << "\n"
      << format_olc(olc) << "\n"
      << format_piccolo_can(piccolo) << "\n"
      << format_blheli(blheli) << "\n"
      << format_nmea_output(nmea) << "\n"
      << format_follow(follow) << "\n"
      << format_leak_detector(leak) << "\n"
      << format_wheel_encoder(wheel) << "\n"
      << format_quicktune(quicktune) << "\n"
      << format_tuning(tuning) << "\n"
      << format_torqeedo(torqeedo) << "\n"
      << format_romfs(romfs) << "\n"
      << format_kde_can(kde) << "\n"
      << format_fettec(fettec) << "\n"
      << format_radio(radio) << "\n"
      << format_sbus_out(sbus) << "\n"
      << format_serial_led(serled) << "\n"
      << format_servo_relay_events(srv_evt) << "\n"
      << format_rc_map(rcmap) << "\n"
      << format_storage_manager(storage) << "\n"
      << format_temp_calibration(tempcal) << "\n"
      << format_autotune(autotune) << "\n"
      << format_prec_land(precland) << "\n"
      << format_volz(volz) << "\n"
      << format_robotis_servo(robotis) << "\n"
      << format_onvif(onvif) << "\n"
      << format_irlock(irlock) << "\n"
      << format_icengine(icengine) << "\n"
      << format_ramtron(ramtron) << "\n"
      << format_lightware(lightware) << "\n"
      << format_board_config(board) << "\n"
      << format_autorotation(autorot) << "\n"
      << format_navigation(nav) << "\n"
      << format_inertial_nav(inav) << "\n"
      << format_external_ahrs(xahrs) << "\n"
      << format_nav_ekf(ekf) << "\n"
      << format_internal_error(ierr) << "\n"
      << format_ar_motors(armot) << "\n"
      << format_ar_wpnav(arwp) << "\n"
      << format_hal_linux(hallx) << "\n"
      << format_hal_empty(halempty) << "\n"
      << format_custom_control(cust) << "\n"
      << format_input_manager(inputm) << "\n"
      << format_ac_pid(pid) << "\n"
      << format_sprayer(spray) << "\n"
      << format_ap_avoidance(apavoid) << "\n"
      << format_dal(dal) << "\n"
      << format_gyro_fft(fft) << "\n"
      << format_check_firmware(fw) << "\n"
      << format_iomcu(iomcu) << "\n"
      << format_accel_cal(acccal) << "\n"
      << format_adc(adc) << "\n"
      << format_button(btn) << "\n"
      << format_csv_reader(csv) << "\n"
      << format_custom_rotations(crot) << "\n"
      << format_dac(dac) << "\n"
      << format_declination(decl) << "\n"
      << format_efi(efi) << "\n"
      << format_external_control(extctl) << "\n"
      << format_gsof(gsof) << "\n"
      << format_hal_esp32(halesp) << "\n"
      << format_hal_qurt(halqurt) << "\n"
      << format_js_button(jsbtn) << "\n"
      << format_json(json) << "\n"
      << format_module(mod) << "\n"
      << format_multi_heap(mheap);
  return oss.str();
}

} // namespace vrp
