#ifndef FSM_STATES_H
#define FSM_STATES_H

#include <stdint.h>

/**
 * @brief Core states for the robot control system.
 */
enum class State {
    IDLE,               // System is stationary, waiting for start command
    TRACKING,           // Normal line following operation
    SEARCHING,          // Lost the line, attempting to recover
    EMERGENCY_STOP,     // Safety shutoff due to error or user intervention
    CALIBRATING         // Sensor calibration mode
};

/**
 * @brief System telemetry and sensor data structure.
 */
struct SystemState {
    State currentState;
    State previousState;
    uint32_t lastStateChange;
    
    int16_t leftSpeed;
    int16_t rightSpeed;
    
    bool lineDetected;
    uint32_t lastLineSeen;
    
    bool heartbeatActive;
    uint32_t lastHeartbeat;
};

#endif // FSM_STATES_H
