# Hardware Abstraction Layer (HAL)

This directory contains abstract interfaces for all hardware components.
Implementations are provided in platform-specific directories under platforms/.

Interfaces:
- Imu.hpp: Inertial Measurement Unit interface
- Baro.hpp: Barometric pressure sensor interface
- Servo.hpp: Servo motor interface
- Clock.hpp: Timekeeping interface
- Transport.hpp: Communication interface (UART, SPI, etc.)
- Storage.hpp: Persistent storage interface

Each interface defines pure virtual methods that must be implemented
by platform-specific concrete classes.