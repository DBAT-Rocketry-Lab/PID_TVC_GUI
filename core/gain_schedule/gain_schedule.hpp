#ifndef CORE_GAIN_SCHEDULE_HPP
#define CORE_GAIN_SCHEDULE_HPP

namespace tvc {
namespace core {

/**
 * @brief Gain Schedule for PID Controller
 *
 * Adjusts PID gains based on operating conditions (e.g., thrust level, velocity).
 * Implements a lookup table or interpolation scheme for gain scheduling.
 */
class GainSchedule {
public:
    /**
     * @brief Constructor
     */
    GainSchedule();

    /**
     * @brief Default destructor
     */
    ~GainSchedule() = default;

    /**
     * @brief Initialize the gain schedule
     * @return true if successful, false otherwise
     */
    virtual bool initialize() = 0;

    /**
     * @brief Get scheduled gains based on current conditions
     * @param[in]  condition_variable Current condition (e.g., normalized thrust)
     * @param[out] Kp Scheduled proportional gain
     * @param[out] Ki Scheduled integral gain
     * @param[out] Kd Scheduled derivative gain
     * @return true if successful, false otherwise
     */
    virtual bool getGains(float condition_variable,
                          float& Kp, float& Ki, float& Kd) = 0;

    /**
     * @brief Reset gain schedule to nominal conditions
     */
    virtual void reset() = 0;

    /**
     * @brief Load gain schedule from configuration/table
     * @note Implementation-specific (could be from file, hardcoded table, etc.)
     */
    virtual bool loadSchedule() = 0;
};

} // namespace core
} // namespace tvc

#endif // CORE_GAIN_SCHEDULE_HPP