"""Design specs for flight-critical libraries wired in CopterCore / control path."""

from __future__ import annotations

# ap_name -> spec dict for SDD generation
WIRED_LIBRARY_SPECS: dict[str, dict] = {
    "AC_AttitudeControl": {
        "integration": "ControlCore::update_quad",
        "uorb": ["control/attitude", "control/pos"],
        "architecture": (
            "PID cascaded attitude controller with optional position-hold overlay. "
            "Roll/pitch/yaw rate PIDs produce `ControlTorque`; `update_pos` maps "
            "WPNav output and altitude error into lean angles and thrust base."
        ),
        "data_flow": (
            "NavCore/SafetyCore → VehicleSetpoints → ControlCore → "
            "VRP_AC_AttitudeControl::update / update_pos → VRP_Motors::mix_quad."
        ),
        "apis": [
            ("init(max_tilt_deg)", "Initialize PID limits and max lean angle"),
            ("apply_autotune_scale(scale)", "Scale attitude PID gains from AutoTune aux"),
            ("update(attitude, sp, dt_s)", "Compute roll/pitch/yaw torque"),
            ("update_pos(pos, nav, target_z, max_tilt, alt_hold)", "Pos-hold setpoint (POSCTL)"),
        ],
        "tests": ["VRP-TST-C01", "VRP-COPTER-T02", "VRP-TC-COPTER-02"],
    },
    "AC_WPNav": {
        "integration": "NavCore (quad path)",
        "uorb": ["nav/ac_wp"],
        "architecture": (
            "Waypoint navigation: bearing, cross-track error, loiter orbit, RTL home vector, "
            "wp-reached detection. Publishes formatted `ACWPNAV` telemetry."
        ),
        "data_flow": "SafetyCore position + mode → VRP_AC_WPNav::update → WpNavOutput → CopterCore/NavCore.",
        "apis": [
            ("init(params)", "Load cruise speed, wp radius, loiter radius"),
            ("update(pos, mode, home)", "Compute nav output for active modes"),
            ("set_loiter_center(x,y)", "Capture loiter anchor on mode entry"),
        ],
        "tests": ["VRP-TST-N01", "VRP-COPTER-T02", "VRP-TC-COPTER-01"],
    },
    "AC_InputManager": {
        "integration": "CopterCore::build_setpoints (Stabilize/Sport)",
        "uorb": [],
        "architecture": "RC input scaling and dead-zone for stabilize modes.",
        "data_flow": "RC channels → apply_stabilize → scaled RcChannels → attitude setpoint.",
        "apis": [
            ("init()", "Module init"),
            ("update(rc, armed)", "Process RC state"),
            ("apply_stabilize(rc, max_tilt_rad)", "Scale roll/pitch/yaw/throttle"),
        ],
        "tests": ["VRP-TST-X01", "VRP-COPTER-T01", "VRP-TC-COPTER-03"],
    },
    "AC_Avoidance": {
        "integration": "SafetyCore::avoidance → CopterCore overlay",
        "uorb": ["safety/avoidance"],
        "architecture": "Bearing/speed avoidance vector from ADSB/proximity; applied as roll/pitch bias.",
        "data_flow": "ADSB sample → VRP_AC_Avoidance → AvoidanceOutput → CopterCore::apply_avoidance.",
        "apis": [
            ("init()", "Init"),
            ("update(adsb, proximity, armed)", "Compute avoidance output"),
        ],
        "tests": ["VRP-TST-J01", "VRP-COPTER-T04", "VRP-TC-COPTER-04"],
    },
    "AC_PrecLand": {
        "integration": "CopterCore Land mode",
        "uorb": [],
        "architecture": "Range-finder aided precision landing; reduces lean when target valid.",
        "data_flow": "RangeFinder + Land mode → PrecLandState → attitude damping in CopterCore.",
        "apis": [
            ("init()", "Init"),
            ("update(rng, armed, mode)", "Update precision land state"),
        ],
        "tests": ["VRP-TST-T01", "VRP-COPTER-T03", "VRP-TC-COPTER-05"],
    },
    "AC_AutoTune": {
        "integration": "CopterCore → ControlCore autotune_scale",
        "uorb": [],
        "architecture": "Aux1-driven PID scale factor for in-flight tuning.",
        "data_flow": "RC aux1 → AutoTuneState → autotune_scale → AttitudeControl PID scale.",
        "apis": [
            ("init()", "Init"),
            ("update(armed, aux1, dt_ms)", "Update tune percentage"),
        ],
        "tests": ["VRP-TST-T01", "VRP-COPTER-T03", "VRP-TC-COPTER-06"],
    },
    "AC_CustomControl": {
        "integration": "CopterCore overlay",
        "uorb": [],
        "architecture": "Custom roll/pitch overlay on attitude setpoint.",
        "data_flow": "RC + mode → CustomControlState → apply_custom_overlay.",
        "apis": [("init()", "Init"), ("update(armed, roll, pitch)", "Custom overlay state")],
        "tests": ["VRP-TST-X01", "VRP-COPTER-T03", "VRP-TC-COPTER-07"],
    },
    "AC_PID": {
        "integration": "CopterCore cross-track correction",
        "uorb": [],
        "architecture": "PID on cross-track error; output biases roll setpoint.",
        "data_flow": "WpNav cross_track_m → VRP_AC_PID → roll correction in CopterCore.",
        "apis": [("init()", "Init"), ("update(active, error)", "PID step with output")],
        "tests": ["VRP-TST-X01", "VRP-COPTER-T03", "VRP-TC-COPTER-08"],
    },
    "AC_Sprayer": {
        "integration": "CopterCore Auto mode",
        "uorb": [],
        "architecture": "Sprayer pump state from aux2 in Auto mode.",
        "data_flow": "mode Auto + aux2 → SprayerState → telemetry.",
        "apis": [("init()", "Init"), ("update(auto, aux2)", "Sprayer on/off state")],
        "tests": ["VRP-TST-X02", "VRP-COPTER-T03", "VRP-TC-COPTER-09"],
    },
    "AC_Fence": {
        "integration": "SafetyCore fence breach",
        "uorb": ["safety/fence"],
        "architecture": "Geofence cylinder; breach triggers RTL/disarm path.",
        "data_flow": "LocalPosition → VRP_AC_Fence → fence_breached → SafetyCore RTL.",
        "apis": [("init(radius_m)", "Init"), ("update(pos, armed)", "Fence check")],
        "tests": ["VRP-TST-C03", "VRP-TC-COPTER-10"],
    },
    "AP_Landing": {
        "integration": "CopterCore Land mode",
        "uorb": [],
        "architecture": "Multi-phase land: approach, flare, touch-down; throttle from altitude error.",
        "data_flow": "pos + rangefinder → LandingSetpoint → CopterCore thrust in Land.",
        "apis": [
            ("init(flare_alt, land_alt)", "Init land parameters"),
            ("update(pos, rng, dt_s)", "Land phase machine"),
            ("reset()", "Reset land state"),
        ],
        "tests": ["VRP-TST-H02", "VRP-COPTER-T05", "VRP-TC-COPTER-11"],
    },
    "AP_InertialNav": {
        "integration": "CopterCore nav damping",
        "uorb": [],
        "architecture": "Velocity estimate from local position delta; damping on nav attitude.",
        "data_flow": "LocalPosition → InertialNavState → apply_nav_attitude velocity damping.",
        "apis": [("init()", "Init"), ("update(pos, active)", "Velocity state")],
        "tests": ["VRP-TST-W01", "VRP-COPTER-T01", "VRP-TC-COPTER-12"],
    },
    "AP_SurfaceDistance": {
        "integration": "CopterCore AGL hold",
        "uorb": [],
        "architecture": "AGL from rangefinder + pitch compensation; alt adjustment in nav.",
        "data_flow": "RangeFinder → SurfaceDistanceSample → thrust/alt bias in nav attitude.",
        "apis": [("init()", "Init"), ("update(rng, pitch_rad)", "AGL sample")],
        "tests": ["VRP-TST-L01", "VRP-COPTER-T01", "VRP-TC-COPTER-13"],
    },
    "AP_Follow": {
        "integration": "CopterCore Guided + LibraryCore",
        "uorb": [],
        "architecture": "Bearing to follow target; active in Loiter/Auto/Guided.",
        "data_flow": "target XY + pos → FollowState → Guided lean override.",
        "apis": [("init()", "Init"), ("update(mode, tx, ty, x, y)", "Follow bearing")],
        "tests": ["VRP-TST-O02", "VRP-COPTER-T04", "VRP-TC-COPTER-14"],
    },
    "AP_Rally": {
        "integration": "SafetyCore RTL fallback",
        "uorb": ["safety/rally"],
        "architecture": "Rally point list; SmartRTL → Rally → home nav chain.",
        "data_flow": "RallyStatus → SafetyCore nav_target → CopterCore RTL rally nav.",
        "apis": [
            ("init()", "Init default rally"),
            ("target_at(index)", "Rally point coordinates"),
            ("nearest_index(x,y)", "Nearest rally index"),
        ],
        "tests": ["VRP-TST-L02", "VRP-COPTER-T04", "VRP-TC-COPTER-15"],
    },
    "AP_OpticalFlow": {
        "integration": "CopterCore flow loiter",
        "uorb": [],
        "architecture": "Optical flow sample → roll/pitch damping for indoor loiter.",
        "data_flow": "OpticalFlowSample → apply_flow_loiter in nav modes.",
        "apis": [("init()", "Init"), ("update(flow, quality_min)", "Flow sample processing")],
        "tests": ["VRP-TST-K01", "VRP-TC-COPTER-16"],
    },
    "AP_Motors": {
        "integration": "ControlCore::mix_quad",
        "uorb": ["actuators/quad"],
        "architecture": "Quad X mix with spool, yaw headroom, tilt limiting.",
        "data_flow": "thrust + ControlTorque → MotorOutputQuad m1..m4.",
        "apis": [
            ("init(max_tilt_deg)", "Init mix limits"),
            ("mix_quad(thrust, torque, spool, yaw_headroom)", "Motor mixing"),
        ],
        "tests": ["VRP-TST-C01", "VRP-COPTER-T01", "VRP-TC-COPTER-17"],
    },
    "AP_RangeFinder": {
        "integration": "SafetyCore sensors → Landing/PrecLand/Surface",
        "uorb": ["sensors/rng"],
        "architecture": "Rangefinder sample for AGL and precision land.",
        "data_flow": "HAL/sim → RangeFinderSample → Landing, PrecLand, SurfaceDistance.",
        "apis": [("init()", "Init"), ("update(sim_rng)", "Range sample")],
        "tests": ["VRP-TST-H01", "VRP-TC-COPTER-18"],
    },
    "AP_SmartRTL": {
        "integration": "SafetyCore nav_target",
        "uorb": ["safety/smartrtl"],
        "architecture": "Breadcrumb RTL path; preferred over direct home when active.",
        "data_flow": "position history → SmartRTL target → SafetyCore RTL nav.",
        "apis": [("init()", "Init"), ("update(pos, rtl_active)", "Breadcrumb target")],
        "tests": ["VRP-TST-F01", "VRP-TC-COPTER-19"],
    },
    "AP_Arming": {
        "integration": "SafetyCore",
        "uorb": ["safety/arming"],
        "architecture": "Pre-arm checks; arm/disarm state machine.",
        "data_flow": "sensor checks → armed flag → ControlCore gate.",
        "apis": [("init()", "Init"), ("update(checks)", "Arming state")],
        "tests": ["VRP-TST-S01", "VRP-TC-SAFETY-01"],
    },
    "AP_Mission": {
        "integration": "SafetyCore mission engine",
        "uorb": ["nav/mission"],
        "architecture": "Mission item sequencer; WP commands for Auto mode.",
        "data_flow": "mission items → active WP → NavCore target.",
        "apis": [("init()", "Init"), ("advance(pos)", "Mission progression")],
        "tests": ["VRP-TST-B01", "VRP-TST-N01", "VRP-TC-MISSION-01"],
    },
}

COPTER_MODULE_SPEC = {
    "module": "CopterCore",
    "path": "src/modules/copter_core/",
    "dal": "B",
    "hlrd": "VRP-HLRD-003",
    "architecture": (
        "Orchestrates multicopter flight modes (Stabilize, Sport, AltHold, Loiter, "
        "Auto, RTL, Land, Guided). Integrates AC_* aux libraries and produces "
        "VehicleSetpoints for ControlCore."
    ),
    "data_flow": (
        "SafetyCore + NavCore → CopterCore::build_setpoints → VehicleCore → "
        "ControlCore → VRP_Motors."
    ),
    "tests": [
        "VRP-COPTER-T01",
        "VRP-COPTER-T02",
        "VRP-COPTER-T03",
        "VRP-COPTER-T04",
        "VRP-COPTER-T05",
        "VRP-TC-COPTER-01",
    ],
}
