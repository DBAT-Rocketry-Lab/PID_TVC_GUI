You are working in my repo for a model-rocket thrust vector control (TVC)
project. Read this whole brief before touching anything.

## Project goal
Build the firmware and tooling to tune and run a PID-based TVC controller.
Hardware: MPU6050 IMU, a barometer, hobby servos (gimbal). Right now we are
building a PID TUNING RIG on an ESP32 (WiFi lets a GUI tune gains live).
Later the same flight logic will be ported to an STM32. Do not target
Arduino Nano.

## Architecture rule (most important)
Flight logic must be hardware-independent so porting = rewriting only the
platform layer.

  core/        PID, attitude estimator, thrust-curve gain schedule, flight
               state machine. Plain C++17. NO Arduino/ESP-IDF/STM32 headers,
               no delay(), no Serial, no dynamic allocation in the loop.
  hal/         Abstract interfaces only: Imu, Baro, Servo, Clock, Transport,
               Storage.
  platforms/   esp32/ now; stm32/ later. Implements hal/ interfaces.
  sim/         Host-side (PC) plant simulator that runs the SAME core/ code.
  tests/       Unit tests for core/ that run on the PC (no hardware).
  tools/gui/   Existing GUI (leave alone until I ask).

## Control model (use this, don't invent another)
Single axis first, pivot at the CG (not the gimbal joint).
  Torque from gimbaled thrust: tau = F * L * sin(delta)
  Dynamics: I * theta_ddot = -tau
  PID outputs a desired restoring torque; convert to gimbal angle with
  delta_cmd = asin(clamp(tau_cmd / (L * F(t)), -1, 1)), then clamp to the
  servo's max deflection.
  F(t) comes from a thrust-curve lookup table indexed by time since
  ignition (CSV loaded at build/run time; use a placeholder constant curve
  until I supply real static-fire data).
  Starting gains from: Kp = I*wn^2/(F*L), Kd = 2*zeta*wn*I/(F*L).
  Implement PID with anti-windup, filtered derivative, output saturation.
  Control is single-axis for now; structure code so a second axis can be
  added later without rewrites.

## Conventions (write these into docs/conventions.md first)
Units: degrees for angles in the API, seconds, meters, newtons. Define the
sign of positive attitude error and positive gimbal deflection explicitly.
Fixed control loop rate configured in one place (default 200 Hz).

## What to do now, in order. Stop and show me results after each phase.
Phase 0 - Explore: inspect the repo, summarize what exists, and propose a
          concrete file layout and build system (I expect PlatformIO for
          ESP32 + a CMake or similar target for host tests/sim). Wait for
          my OK before restructuring anything.
Phase 1 - Scaffold: create the directory layout, docs/conventions.md, the
          hal/ interfaces, and the build configs. Pins, servo limits, L, I,
          and F values go in a single config header with clearly marked
          TODO placeholders. NEVER guess pin numbers or physical values;
          ask me.
Phase 2 - core/: estimator (complementary filter), PID, gain schedule,
          state machine (pad idle -> armed -> boost -> coast -> descent;
          launch detect from accelerometer, baro only for apogee/events).
          Write unit tests alongside. All tests must pass on the PC.
Phase 3 - sim/: plant (I*theta_ddot = -F*L*sin(delta)), servo model
          (latency, slew limit, deflection limit), IMU noise, thrust
          curve. Run the real core/ PID in closed loop, output CSV and a
          plot of angle, command, and torque vs time. Report settling time
          and overshoot.
Phase 4 - platforms/esp32/: implement the HAL for MPU6050, barometer, servo
          PWM; fixed-rate control task; gyro bias calibration at startup.
          WiFi/telemetry runs in a SEPARATE task and must never block or
          delay the control loop.
Phase 5 - Protocol: a small framed, transport-agnostic message set.
          Telemetry out: angle, error, P/I/D terms, servo command, state.
          Commands in: set/get gains, arm, disarm, set setpoint. Document
          it in docs/protocol.md. Do NOT build the GUI yet; stop here.

## Working rules
- Make small, focused commits with clear messages; one concern per commit.
- Before adding any dependency, tell me what it is and why.
- If something is ambiguous (hardware detail, sign convention, units),
  ask instead of assuming.
- Keep core/ free of platform code. If you're tempted to include a
  hardware header there, put it behind a hal/ interface instead.
- Don't modify tools/gui/ or existing files outside the plan without
  asking.
- Safety defaults: servo deflection clamped, controller starts disarmed,
  output goes to neutral on any fault or lost command.
- After each phase, summarize what you did, what you tested, and what's
  still uncertain.

Start with Phase 0 only.
