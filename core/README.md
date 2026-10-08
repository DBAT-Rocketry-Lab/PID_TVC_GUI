# Core Module

This directory contains the platform-independent flight logic for the TVC system.
All code here is written in standard C++17 with no platform-specific dependencies.

Subdirectories:
- estimator/: Attitude estimation algorithms (complementary filter, etc.)
- pid/: PID controller implementation with anti-windup and filtered derivative
- gain_schedule/: Thrust-curve based gain scheduling
- state_machine/: Flight state machine (idle → armed → boost → coast → descent)

Dependencies:
- Only depends on HAL interfaces (via dependency injection or abstract base classes)
- No direct hardware access
- No operating system specific code