#ifndef SYSTEM_SAFETY_H
#define SYSTEM_SAFETY_H

/**
 * @brief Safety Thresholds and Constants
 */

// Power limits
const int MAX_PWM = 200;            // Maximum allowed PWM output
const int STALL_PWM_THRESHOLD = 80; // Minimum PWM that should cause movement

// Timeouts
const unsigned long HEARTBEAT_TIMEOUT_MS = 2000;  // Stop if no command for 2s
const unsigned long STALL_DETECTION_MS = 3000;    // Trigger stall if no movement for 3s
const unsigned long LINE_LOSS_TIMEOUT_MS = 1500;  // Enter searching if line lost for 1.5s

// Control Loop Frequencies
const int CONTROL_HZ = 100;
const unsigned long CONTROL_INTERVAL_MS = 1000 / CONTROL_HZ;

#endif // SYSTEM_SAFETY_H
