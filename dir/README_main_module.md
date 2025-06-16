# Main Module Documentation (main.ino & main.h)

## Overview
This module is the core of the robot project, responsible for integrating all hardware and software components, managing operation modes, and orchestrating the robot's behavior. It consists of the main Arduino sketch (`main.ino`) and its primary header (`main.h`).

---

## main.ino
### Purpose
- Implements the main control loop for the robot.
- Handles mode switching (joystick, voice, Bluetooth).
- Integrates all hardware modules: motors, ultrasonic sensors, LEDs, joystick, and voice module.

### Key Sections
- **Global Variables**: State for joystick, ultrasonic sensors, mode, LEDs, and voice recognition.
- **Motor Control Functions**: Low-level and high-level movement commands.
- **setup()**: Initializes all modules and serial communication.
- **loop()**: Main control loop. Handles mode switching, sensor reading, and delegates control to the appropriate mode handler.

### Operation Modes
- `CONTROL_BY_JOYSTICK`: Manual control via joystick.
- `CONTROL_BY_VOICE`: Voice command control.
- `CONTROL_BY_BLUETOOTH`: Remote control via Bluetooth.

### Key Functions
- `setup()`, `loop()`
- `motor_1_forward()`, `motor_1_backward()`, `motor_2_forward()`, etc.
- `ROBOT_FORWARD()`, `ROBOT_BACKWARD()`, etc.
- `stop()`, `forward()`, `backward()`, etc.
- `is_valid_distance(int distance)`

### Sensor Integration
- **Ultrasonic Sensors**: For obstacle detection.
- **Joystick**: For manual control.
- **Voice Module**: For voice commands.
- **Bluetooth**: For remote commands.

### Mode Switching
- Cycles through modes using the joystick button.

---

## main.h
### Purpose
- Provides global definitions, includes, and function prototypes for the project.

### Key Definitions
- `MINIMUM_ACCEPTED_DISTANCE`: Minimum safe distance for obstacle avoidance.
- `mode_t`: Enum for control modes.
- `extern int back_dist, front_dist;`: Global ultrasonic sensor readings.

### Function Prototypes
- Bluetooth, motor, and robot movement functions.

### Integration
- Included by all major source files for consistent definitions and prototypes.

---

## Notes
- Designed for modularity and easy extension.
- All hardware-specific pin assignments are defined at the top or in included headers.
- Ensures consistent use of constants and function signatures across the codebase. 