cmake_minimum_required(VERSION 3.16)
project(PID_TVC_GUI LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Project version
set(PROJECT_VERSION "0.1.0")

# Directories
set(CORE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/core)
set(HAL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/hal)
set(SIM_DIR ${CMAKE_CURRENT_SOURCE_DIR}/sim)
set(TESTS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/tests)

# Include directories
include_directories(
    ${CORE_DIR}
    ${HAL_DIR}
    ${SIM_DIR}
)

# Core library
add_library(core_statlib
    ${CORE_DIR}/estimator/estimator.cpp
    ${CORE_DIR}/pid/pid_controller.cpp
    ${CORE_DIR}/gain_schedule/gain_schedule.cpp
    ${CORE_DIR}/state_machine/state_machine.cpp
)

# Simulation executable
add_executable(tvc_sim
    ${SIM_DIR}/sim_main.cpp
)

target_link_libraries(tvc_sim PRIVATE core_statlib)

# Tests
enable_testing()
add_executable(tvc_tests
    ${TESTS_DIR}/test_estimator.cpp
    ${TESTS_DIR}/test_pid.cpp
    ${TESTS_DIR}/test_gain_schedule.cpp
    ${TESTS_DIR}/test_state_machine.cpp
)

target_link_libraries(tvc_tests PRIVATE core_statlib)

# Add tests to CTest
add_test(NAME estimator_test COMMAND tvc_tests --gtest_filter=*Estimator*)
add_test(NAME pid_test COMMAND tvc_tests --gtest_filter=*PID*)
add_test(NAME gain_schedule_test COMMAND tvc_tests --gtest_filter=*GainSchedule*)
add_test(NAME state_machine_test COMMAND tvc_tests --gtest_filter=*StateMachine*)

# Install rules
install(TARGETS tvc_sim tvc_tests DESTINATION bin)
install(TARGETS core_statlib DESTINATION lib)
install(DIRECTORY docs/ DESTINATION share/doc/${PROJECT_NAME})