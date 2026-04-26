import { describe, it, expect, vi } from 'vitest';

/**
 * Mocking the hardware and state for testing logic
 */
class MockRobot {
    constructor() {
        this.state = 'IDLE';
        this.lastHeartbeat = Date.now();
        this.motors = { left: 0, right: 0 };
    }

    update(currentTime) {
        if (currentTime - this.lastHeartbeat > 2000) {
            this.state = 'EMERGENCY_STOP';
            this.motors = { left: 0, right: 0 };
        }
    }
}

describe('System Robustness & Fail-Safe Logic', () => {
    it('should enter EMERGENCY_STOP if heartbeat is lost for > 2000ms', () => {
        const robot = new MockRobot();
        const startTime = Date.now();
        
        // Simulate time passing without heartbeat update
        robot.update(startTime + 2500);
        
        expect(robot.state).toBe('EMERGENCY_STOP');
        expect(robot.motors.left).toBe(0);
        expect(robot.motors.right).toBe(0);
    });

    it('should maintain IDLE state by default', () => {
        const robot = new MockRobot();
        expect(robot.state).toBe('IDLE');
    });
});
