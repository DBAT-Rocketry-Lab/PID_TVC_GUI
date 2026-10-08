# TVC Project Conventions

## Units
- Angles: degrees (in API/internal calculations where specified)
- Time: seconds
- Distance: meters  
- Force: newtons
- Mass: kilograms

## Sign Conventions
### Attitude Error
- Positive attitude error: [TO BE DEFINED BASED ON COORDINATE SYSTEM]
- Negative attitude error: [TO BE DEFINED BASED ON COORDINATE SYSTEM]

### Gimbal Deflection
- Positive gimbal deflection: [TO BE DEFINED BASED ON COORDINATE SYSTEM]  
- Negative gimbal deflection: [TO BE DEFINED BASED ON COORDINATE SYSTEM]

## Control Loop Rate
- Fixed control loop rate: 200 Hz (default)
- Configured in: [TO BE SPECIFIED - likely in a central config header]
- Period: 5ms (1/200)

## Coordinate System
[TO BE DEFINED - should specify:
- Reference frames (body, inertial, etc.)
- Axis orientations (x-forward, y-right, z-down or similar)
- Rotation directions (right-hand rule applications)]

## Temperature
- Kelvin (K) for thermodynamic calculations
- Celsius (°C) for sensor interfaces where applicable

## Voltage
- Volts (V) for electrical measurements

## Current
- Amperes (A) for electrical measurements