# Simulation

This directory contains host-side simulation components that allow
testing and development without physical hardware.

The simulation runs the exact same core/ code as the target hardware,
enabling validation of flight logic in a controlled environment.

Subdirectories:
- plant/: Physics simulation (rigid body dynamics, thrust modeling)
- sensor_models/: Realistic sensor noise and error models
- io/: Simulated I/O interfaces (GUI, network, etc.)

Key benefits:
- Test core logic without hardware risks
- Rapid iteration and debugging
- Automated testing capabilities
- Hardware-in-the-loop (HIL) preparation