# System Safety & Robustness Design

This document outlines the fail-safe mechanisms implemented in the `adv-12-unit-code-logic` project to ensure reliable operation under abnormal conditions.

## Disaster Scenarios & Defense Strategies

### 1. Heartbeat Loss (Communication Failure)
- **Scenario**: The robot loses contact with the control dashboard/remote.
- **Detection**: `millis() - lastHeartbeat > HEARTBEAT_TIMEOUT_MS`.
- **Action**: Immediate transition to `EMERGENCY_STOP`. Motors are cut to 0 PWM.
- **Recovery**: Requires a system reset or specific "RE-ARM" command.

### 2. Motor Stall Detection
- **Scenario**: Motors are powered but wheels are physically obstructed (stalled).
- **Detection**: PWM output > `STALL_PWM_THRESHOLD` AND encoder ticks = 0 for `STALL_DETECTION_MS`.
- **Action**: Transition to `EMERGENCY_STOP` to prevent motor/driver burnout.
- **Recovery**: Manual inspection and reset.

### 3. Total Line Loss (Orientation Failure)
- **Scenario**: Sensors report all white for an extended period during `TRACKING`.
- **Detection**: `!lineDetected` for > `LINE_LOSS_TIMEOUT_MS` during `SEARCHING`.
- **Action**: Transition to `EMERGENCY_STOP` to avoid wandering off-course indefinitely.
- **Recovery**: Return robot to the line and restart.

## Loop Performance Analysis
- **Goal**: Maintain a stable 10ms (100Hz) control loop.
- **Verification**: Use Serial Plotter to monitor `Loop_Interval`. Any spikes indicate blocking code (e.g., `delay()` or long `Serial.print`).
