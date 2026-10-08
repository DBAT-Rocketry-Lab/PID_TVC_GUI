#include "pid_controller.hpp"

namespace tvc {
namespace core {

PIDController::PIDController(float Kp, float Ki, float Kd, float dt,
                             float output_min, float output_max)
    : Kp_(Kp), Ki_(Ki), Kd_(Kd), dt_(dt),
      output_min_(output_min), output_max_(output_max),
      integral_(0.0f), prev_error_(0.0f), derivative_filtered_(0.0f) {
    // Validate time step
    if (dt_ <= 0.0f) {
        // In a real system, we might throw an exception or use a default
        // For now, we'll set a minimal reasonable value
        dt_ = 0.001f; // 1ms
    }
}

float PIDController::compute(float error) {
    // Proportional term
    float proportional = Kp_ * error;

    // Integral term with anti-windup (basic clamping)
    integral_ += error * dt_;
    // Anti-windup: clamp integral to prevent excessive buildup
    float integral_output = Ki_ * integral_;
    if (integral_output > output_max_) {
        integral_ = output_max_ / Ki_; // Clamp integral
    } else if (integral_output < output_min_) {
        integral_ = output_min_ / Ki_; // Clamp integral
    }

    // Derivative term with filtering
    float derivative_raw = (error - prev_error_) / dt_;
    // First-order filter: y[n] = alpha * x[n] + (1-alpha) * y[n-1]
    derivative_filtered_ = derivative_filter_alpha_ * derivative_raw +
                          (1.0f - derivative_filter_alpha_) * derivative_filtered_;
    float derivative = Kd_ * derivative_filtered_;

    // Compute output
    float output = proportional + integral_ + derivative;

    // Apply output limits
    if (output > output_max_) {
        output = output_max_;
    } else if (output < output_min_) {
        output = output_min_;
    }

    // Save error for next iteration
    prev_error_ = error;

    return output;
}

void PIDController::reset() {
    integral_ = 0.0f;
    prev_error_ = 0.0f;
    derivative_filtered_ = 0.0f;
}

void PIDController::setGains(float Kp, float Ki, float Kd) {
    Kp_ = Kp;
    Ki_ = Ki;
    Kd_ = Kd;
}

void PIDController::getGains(float& Kp, float& Ki, float& Kd) const {
    Kp = Kp_;
    Ki = Ki_;
    Kd = Kd_;
}

void PIDController::setOutputLimits(float min, float max) {
    output_min_ = min;
    output_max_ = max;
}

void PIDController::getOutputLimits(float& min, float& max) const {
    min = output_min_;
    max = output_max_;
}

} // namespace core
} // namespace tvc