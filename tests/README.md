# Tests

This directory contains unit tests for the core/ module.
All tests run on the host PC (no hardware required).

Testing framework: Google Test (or similar C++ testing framework)

Test organization:
- test_estimator.cpp: Tests for attitude estimation algorithms
- test_pid.cpp: Tests for PID controller (including anti-windup)
- test_gain_schedule.cpp: Tests for thrust-curve gain scheduling
- test_state_machine.cpp: Tests for flight state machine transitions

Testing principles:
- Test core logic in isolation (mock HAL interfaces)
- Verify mathematical correctness
- Test edge cases and error conditions
- Ensure deterministic behavior
- Maintain high test coverage for safety-critical code

To run tests:
1. Build: make test (or ctest)
2. Execute: ./tvc_tests
3. Results: See console output or test reports