#ifndef CORE_STATE_MACHINE_HPP
#define CORE_STATE_MACHINE_HPP

namespace tvc {
namespace core {

/**
 * @brief Flight State Machine
 *
 * Manages the discrete states of the vehicle throughout its flight profile.
 * States typically include: idle, armed, boost, coast, descent, landing, etc.
 * Transitions are triggered by conditions like time, acceleration, altitude, etc.
 */
class StateMachine {
public:
    /**
     * @brief Flight states
     */
    enum class State {
        UNKNOWN = 0,
        IDLE,           // Waiting for arm command
        ARMED,          // Armed but waiting for launch
        BOOST,          // Powered ascent
        COAST,          // Unpowered ascent after burnout
        DESCENT,        // Descending under drogue/main chute
        LANDING,        // Final approach to ground
        RECOVERED,      // Safely on ground
        ERROR           // Error state
    };

    /**
     * @brief Constructor
     */
    StateMachine();

    /**
     * @brief Default destructor
     */
    ~StateMachine() = default;

    /**
     * @brief Initialize the state machine
     * @return true if successful, false otherwise
     */
    virtual bool initialize() = 0;

    /**
     * @brief Update state machine based on current conditions
     * @param[in]  time_since_launch_seconds Time since launch (s)
     * @param[in]  acceleration_magnitude    Total acceleration magnitude (m/s^2)
     * @param[in]  altitude_meters           Current altitude (m)
     * @param[in]  vertical_velocity_mps     Vertical velocity (m/s, + = up)
     * @param[out] current_state             Current flight state
     * @return true if state update successful, false otherwise
     */
    virtual bool update(float time_since_launch_seconds,
                        float acceleration_magnitude,
                        float altitude_meters,
                        float vertical_velocity_mps,
                        State& current_state) = 0;

    /**
     * @brief Get current state without triggering transition logic
     * @return Current flight state
     */
    virtual State getCurrentState() const = 0;

    /**
     * @brief Reset state machine to initial state
     */
    virtual void reset() = 0;

    /**
     * @brief Set transition thresholds/parameters
     * @note Specific parameters depend on implementation
     */
    virtual void setTransitionParameters(/* implementation-specific */) = 0;
};

} // namespace core
} // namespace tvc

#endif // CORE_STATE_MACHINE_HPP
