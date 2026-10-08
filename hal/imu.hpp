#ifndef HAL_IMU_HPP
#define HAL_IMU_HPP

namespace tvc {
namespace hal {

/**
 * @brief Abstract interface for Inertial Measurement Unit
 */
class Imu {
public:
    virtual ~Imu() = default;

    /**
     * @brief Initialize the IMU
     * @return true if successful, false otherwise
     */
    virtual bool initialize() = 0;

    /**
     * @brief Read accelerometer data (m/s^2)
     * @param[out] ax Acceleration X axis
     * @param[out] ay Acceleration Y axis
     * @param[out] az Acceleration Z axis
     * @return true if successful, false otherwise
     */
    virtual bool readAccelerometer(float& ax, float& ay, float& az) = 0;

    /**
     * @brief Read gyroscope data (rad/s)
     * @param[out] gx Gyroscope X axis
     * @param[out] gy Gyroscope Y axis
     * @param[out] gz Gyroscope Z axis
     * @return true if successful, false otherwise
     */
    virtual bool readGyroscope(float& gx, float& gy, float& gz) = 0;

    /**
     * @brief Read magnetometer data (μT) - optional
     * @param[out] mx Magnetometer X axis
     * @param[out] my Magnetometer Y axis
     * @param[out] mz Magnetometer Z axis
     * @return true if successful, false otherwise
     */
    virtual bool readMagnetometer(float& mx, float& my, float& mz) {
        // Optional implementation - return false if not available
        (void)mx; (void)my; (void)mz;
        return false;
    }

    /**
     * @brief Get IMU temperature (°C) - optional
     * @param[out] temperature Temperature in Celsius
     * @return true if successful, false otherwise
     */
    virtual bool getTemperature(float& temperature) {
        // Optional implementation
        (void)temperature;
        return false;
    }
};

} // namespace hal
} // namespace tvc

#endif // HAL_IMU_HPP