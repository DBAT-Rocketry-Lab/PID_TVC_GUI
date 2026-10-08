#ifndef CORE_ESTIMATOR_HPP
#define CORE_ESTIMATOR_HPP

namespace tvc {
namespace core {

/**
 * @brief Attitude Estimator (e.g., complementary filter, Kalman filter)
 *
 * Fuses sensor data to estimate vehicle attitude.
 * Designed to work with IMU (accelerometer, gyroscope) and optionally
 * other sensors like barometers, magnetometers, or GPS.
 */
class Estimator {
public:
    /**
     * @brief Constructor
     * @param dt Time step (seconds) - must be > 0
     */
    explicit Estimator(float dt);

    /**
     * @brief Default destructor
     */
    ~Estimator() = default;

    /**
     * @brief Initialize the estimator
     * @return true if successful, false otherwise
     */
    virtual bool initialize() = 0;

    /**
     * @brief Update estimator with new sensor data
     * @param accel_x Accelerometer X axis (m/s^2)
     * @param accel_y Accelerometer Y axis (m/s^2)
     * @param accel_z Accelerometer Z axis (m/s^2)
     * @param gyro_x Gyroscope X axis (rad/s)
     * @param gyro_y Gyroscope Y axis (rad/s)
     * @param gyro_z Gyroscope Z axis (rad/s)
     * @param[out] pitch Estimated pitch angle (radians)
     * @param[out] yaw Estimated yaw angle (radians)
     * @param[out] roll Estimated roll angle (radians)
     * @return true if successful, false otherwise
     */
    virtual bool update(float accel_x, float accel_y, float accel_z,
                        float gyro_x, float gyro_y, float gyro_z,
                        float& pitch, float& yaw, float& roll) = 0;

    /**
     * @brief Reset estimator state
     */
    virtual void reset() = 0;

    /**
     * @brief Set estimator parameters (gain, etc.)
     * @note Specific parameters depend on estimator type
     */
    virtual void setParameters(/* estimator-specific params */) = 0;

protected:
    // Time step
    float dt_;
};

} // namespace core
} // namespace tvc

#endif // CORE_ESTIMATOR_HPP