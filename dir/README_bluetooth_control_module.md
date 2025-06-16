# Bluetooth Control Module Documentation (bluetooth_control.cpp)

## Overview
This module manages all Bluetooth-based control for the robot. It handles Bluetooth communication, interprets commands, and integrates with the robot's movement and obstacle avoidance systems.

---

## bluetooth_control.cpp
### Purpose
- Handles Bluetooth serial communication.
- Interprets and processes both remote and voice commands received via Bluetooth.
- Integrates with the robot's movement and obstacle avoidance logic.

### Key Sections
- **Bluetooth Mode Management**: Supports both remote and voice control modes via Bluetooth.
- **Bluetooth Initialization**: Sets up the serial connection for Bluetooth communication.
- **Command Processing**: Reads and interprets incoming Bluetooth commands, switching between remote and voice control as needed.
- **Movement and Obstacle Avoidance**: Integrates with the robot's movement functions and uses ultrasonic sensors to avoid obstacles.

### Key Functions
- `bluetooth_init()`: Initializes the Bluetooth serial connection.
- `process_bluetooth_commands()`: Reads and processes incoming Bluetooth commands, dispatching to the appropriate handler.
- `process_remote_command(char command)`: Handles direct movement commands (forward, backward, left, right, stop) from a remote.
- `process_voice_command(char command)`: Handles movement commands received as voice commands via Bluetooth.
- `check_obstacles_while_moving()`: Continuously checks for obstacles while the robot is moving and stops if necessary.
- `motor_is_moving_forward()`, `motor_is_moving_backward()`: Helper functions to determine the current movement direction based on motor pins.

### Command Protocol
- **Remote Commands**: 'F' (forward), 'B' (backward), 'L' (left), 'R' (right), 'S' (stop)
- **Voice Commands**: '^' (forward), '-' (backward), '<' (left), '>' (right), '*' (stop)

### Obstacle Avoidance
- Uses the ultrasonic sensors (`front_ultrasonic`, `back_ultrasonic`) to check for obstacles before and during movement.
- Stops the robot if an obstacle is detected within the minimum accepted distance.

### Integration
- Relies on global variables and functions defined in `main.h` and `ultrasonic.h`.
- Works in conjunction with the main control loop in `main.ino`.

---

## Notes
- The file is modular and can be extended to support additional Bluetooth command types or more complex behaviors. 