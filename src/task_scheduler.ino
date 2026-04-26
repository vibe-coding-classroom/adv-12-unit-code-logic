#include "fsm_states.h"
#include "system_safety.h"

extern SystemState robotState;
extern void updateFSM();

unsigned long lastControlTime = 0;
unsigned long lastTelemetryTime = 0;

void setup() {
    Serial.begin(115200);
    
    // Initialize Robot State
    robotState.currentState = State::IDLE;
    robotState.lastHeartbeat = millis();
    
    Serial.println("System Initialized. Mode: IDLE");
}

void loop() {
    unsigned long currentTime = millis();

    // TASK 1: High-Frequency Control Loop (100Hz)
    if (currentTime - lastControlTime >= CONTROL_INTERVAL_MS) {
        lastControlTime = currentTime;
        
        // 1. Read Sensors
        readSensors();
        
        // 2. Run FSM Logic
        updateFSM();
        
        // 3. Apply Motor Outputs
        applyMotors();
    }

    // TASK 2: Low-Frequency Telemetry (10Hz)
    if (currentTime - lastTelemetryTime >= 100) {
        lastTelemetryTime = currentTime;
        sendTelemetry();
    }
}

void readSensors() {
    // Implement sensor reading and update robotState.lineDetected, lastLineSeen
}

void applyMotors() {
    // Implement PWM output clamping using MAX_PWM
    int left = constrain(robotState.leftSpeed, -MAX_PWM, MAX_PWM);
    int right = constrain(robotState.rightSpeed, -MAX_PWM, MAX_PWM);
    
    // analogWrite(LEFT_MOTOR_PIN, abs(left));
    // ...
}

void sendTelemetry() {
    // Non-blocking serial output for debugging/plotting
    Serial.print("State:");
    Serial.print((int)robotState.currentState);
    Serial.print(" L:");
    Serial.print(robotState.leftSpeed);
    Serial.print(" R:");
    Serial.println(robotState.rightSpeed);
}
