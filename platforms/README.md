# Platform Implementations

This directory contains platform-specific implementations of the HAL interfaces.
Each subdirectory corresponds to a supported hardware platform.

Current platforms:
- esp32/: ESP32-specific implementations
- stm32/: STM32-specific implementations (planned)

Each platform directory should contain:
- src/: Source files implementing HAL interfaces
- include/: Header files
- PlatformIO.ini or CMakeLists.txt: Platform-specific build configuration

Implementation requirements:
- Include corresponding hal/ headers
- Implement all pure virtual methods from HAL interfaces
- Handle hardware initialization and configuration
- Manage hardware-specific details (registers, timing, etc.)
- Keep platform code isolated from core logic