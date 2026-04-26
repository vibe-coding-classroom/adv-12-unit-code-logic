#include "fsm_states.h"
#include "system_safety.h"
#include <Arduino.h>

SystemState robotState;

/**
 * @brief Handle behavior for the IDLE state.
 */
void handleIdle() {
    robotState.leftSpeed = 0;
    robotState.rightSpeed = 0;
    
    // Transition logic: Start command received?
    // if (startCommandReceived) transitionTo(State::TRACKING);
}

/**
 * @brief Handle behavior for the TRACKING state.
 */
void handleTracking() {
    // Implement PID Line Following logic here
    // robotState.leftSpeed = baseSpeed + correction;
    // robotState.rightSpeed = baseSpeed - correction;
    
    // Transition logic: Line lost?
    if (!robotState.lineDetected && (millis() - robotState.lastLineSeen > 50)) {
        // transitionTo(State::SEARCHING);
    }
}

/**
 * @brief Handle behavior for the SEARCHING state.
 */
void handleSearching() {
    // Implement line searching strategy (e.g., spin or sweep)
    
    // Transition logic: Line found?
    if (robotState.lineDetected) {
        // transitionTo(State::TRACKING);
    }
    
    // Transition logic: Search timeout?
    if (millis() - robotState.lastLineSeen > LINE_LOSS_TIMEOUT_MS) {
        // transitionTo(State::EMERGENCY_STOP);
    }
}

/**
 * @brief Handle behavior for the EMERGENCY_STOP state.
 */
void handleEmergencyStop() {
    robotState.leftSpeed = 0;
    robotState.rightSpeed = 0;
    // Manual reset required
}

/**
 * @brief Main FSM dispatcher.
 */
void updateFSM() {
    // Global Safety Check: Heartbeat
    if (millis() - robotState.lastHeartbeat > HEARTBEAT_TIMEOUT_MS) {
        robotState.currentState = State::EMERGENCY_STOP;
    }

    switch (robotState.currentState) {
        case State::IDLE:
            handleIdle();
            break;
        case State::TRACKING:
            handleTracking();
            break;
        case State::SEARCHING:
            handleSearching();
            break;
        case State::EMERGENCY_STOP:
            handleEmergencyStop();
            break;
        default:
            robotState.currentState = State::EMERGENCY_STOP;
            break;
    }
}
