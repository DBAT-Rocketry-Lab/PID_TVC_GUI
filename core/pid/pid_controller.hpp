#ifndef CORE_PID_CONTROLLER_HPP
#define CORE_PID_CONTROLLER_HPP

namespace tvc {
namespace core {

/**
 * @brief PID Controller with anti-windup and filtered derivative
 *
 * Implements a discrete-time PID controller suitable for embedded systems.
 * Features:
 * - Standard PID control: u(t) = Kp*e(t) + Ki*∫e(t)dt + Kd*de(t)/dt
 * - Anti-windup via back-calculation or clamping
 * - Derivative filtering to reduce noise sensitivity
 * - Output saturation limits
 */
class PIDController {
public:
    /**
     * @brief Constructor
     * @param Kp Proportional gain
     * @param Ki Integral gain
     * @param Kd Derivative gain
     * @param dt Time step (seconds) - must be > 0
     * @param output_min Minimum output limit
     * @param output_max Maximum output limit
     */
    PIDController(float Kp, float Ki, float Kd, float dt,
                  float output_min, float output_max);

    /**
     * @brief Default destructor
     */
    ~PIDController() = default;

    /**
     * @brief Compute PID output for current error
     * @param error Current error (setpoint - measurement)
     * @return Control output within [output_min, output_max]
     */
    float compute(float error);

    /**
     * @brief Reset controller state (integral and derivative terms)
     */
    void reset();

    /**
     * @brief Set PID gains
     * @param Kp Proportional gain
     * @param Ki Integral gain
     * @param Kd Derivative gain
     */
    void setGains(float Kp, float Ki, float Kd);

    /**
     * @brief Get current PID gains
     * @param[out] Kp Proportional gain
     * @param[out] Ki Integral gain
     * @param[out] Kd Derivative gain
     */
    void getGains(float& Kp, float& Ki, float& Kd) const;

    /**
     * @brief Set output limits
     * @param min Minimum output
     * @param max Maximum output
     */
    void setOutputLimits(float min, float max);

    /**
     * @brief Get current output limits
     * @param[out] min Minimum output
     * @param[out] max Maximum output
     */
    void getOutputLimits(float& min, float& max) const;

private:
    // Gains
    float Kp_;
    float Ki_;
    float Kd_;

    // Time step
    float dt_;

    // Output limits
    float output_min_;
    float output_max_;

    // State variables
    float integral_;      // Integrated error
    float prev_error_;    // Previous error for derivative
    float derivative_filtered_;  // Filtered derivative term

    // Derivative filter coefficient (0 = no filter, 1 = heavy filtering)
    // Typical values: 0.1 to 0.25
    const float derivative_filter_alpha_ = 0.2f;
};

} // namespace core
} // namespace tvc

#endif // CORE_PID_CONTROLLER_HPP