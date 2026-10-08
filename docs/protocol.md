# TVC Communication Protocol

## Overview
Defines the framed, transport-agnostic message set for communication between:
- Ground station and flight controller
- Flight controller and simulators
- Component-to-component communication within the flight controller

## Message Format
[TO BE DEFINED - small framed messages as specified in claude.md]

### Fields:
- Start delimiter
- Message type/ID
- Length
- Payload
- Checksum/CRC
- End delimiter

## Message Types

### Telemetry (Flight Controller → Ground Station)
- Angle measurements (pitch, yaw, roll)
- Angular rates
- Estimated state
- PID terms (P, I, D)
- Servo commands
- Flight state
- Diagnostic information

### Commands (Ground Station → Flight Controller)
- Set/get PID gains
- Arm/disarm
- Set setpoint (target angles)
- Calibration requests
- Flight mode changes

## Transport Agnosticism
The protocol is designed to work over:
- UART (serial)
- TCP/IP (WiFi/Ethernet)
- UDP
- CAN bus
- SPI
- Other serial transports

## Implementation Notes
- Fixed-size fields for predictable parsing
- Little-endian byte order (unless specified otherwise)
- Optional: Message sequencing for loss detection
- Optional: Timestamp synchronization