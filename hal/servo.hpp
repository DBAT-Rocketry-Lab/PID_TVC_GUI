#ifndef HAL_SERVO_HPP
#define HAL_SERVO_HPP

namespace tvc {
namespace hal {

/**
 * @brief Abstract interface for Servo Motor Control
 */
class Servo {
public:
    virtual ~Servo() = default;

    /**
     * @brief Initialize the servo interface
     * @return true if successful, false otherwise
     */
    virtual bool initialize() = 0;

    /**
     * @brief Set servo position/angle
     * @param angle Desired angle in radians
     * @return true if successful, false otherwise
     */
    virtual bool setAngle(float angle) = 0;

    /**
     * @brief Get current servo position/angle
     * @param[out] angle Current angle in radians
     * @return true if successful, false otherwise
     */
    virtual bool getAngle(float& angle) = 0;

    /**
     * @brief Set servo speed/rate limit (if supported)
     * @param rate Maximum rate of change in rad/s
     * @return true if successful, false otherwise
     */
    virtual bool setRateLimit(float rate) {
        (void)rate;
        return true; // Default implementation - can be overridden
    }

    /**
     * @brief Enable/disable servo torque (if supported)
     * @param enable true to enable torque, false to disable/free spin
     * @return true if successful, false otherwise
     */
    virtual bool setTorqueEnable(bool enable) {
        (void)enable;
        return true; // Default implementation - can be overridden
    }
};

} // namespace hal
} // namespace tvc

#endif // HAL_SERVO_HPP