# Robot Control System Documentation

## Overview

This document provides a comprehensive overview of the robot control system implemented in the Arduino-based robot. The system allows for controlling the robot's movement using either a joystick or voice commands, with safety features to prevent collisions.

## System Components

### Hardware Components
- **Motors**: Two motors controlled through a 2-channel relay module
- **Joystick**: Provides analog X and Y values for directional control
- **Ultrasonic Sensors**: Front and back sensors for obstacle detection
- **Voice Recognition Module**: Enables voice command control

### Control Modes
1. **Joystick Control Mode**: Default mode where the robot is controlled via joystick movements
2. **Voice Control Mode**: Alternative mode where the robot responds to voice commands

## Movement Control System

### Basic Movement Functions

The robot can perform four basic movements:
- **Forward**: Both motors move forward
- **Backward**: Both motors move backward
- **Left**: Left motor moves backward, right motor moves forward
- **Right**: Left motor moves forward, right motor moves backward

### Mixed Direction Control

When the joystick is moved diagonally (indicating a mixed direction), the system intelligently chooses the most appropriate pure direction based on the joystick position. This is accomplished through the following process:

1. **Direction Determination**:
   - The system calculates how far the joystick is from the center in both X and Y axes
   - It compares these distances to determine which direction has the stronger input

2. **Decision Logic**:
   - If Y-axis displacement > X-axis displacement: Choose forward/backward
   - If X-axis displacement > Y-axis displacement: Choose left/right

3. **Safety Checks**:
   - Before moving forward: Check if front distance > minimum accepted distance
   - Before moving backward: Check if back distance > minimum accepted distance
   - If an obstacle is detected, the robot stops

### Implementation Details

#### Mixed Direction Functions

```c++
void forward_left(int x_val, int y_val) {
  if (front_dist > MINIMUM_ACCEPTED_DISTANCE) {
    // Calculate how far the joystick is from center in each direction
    int x_distance_from_center = abs(x_val - 512);
    int y_distance_from_center = abs(y_val - 512);
    
    // Compare the distances to determine which direction is stronger
    if (y_distance_from_center > x_distance_from_center) {
      // Y-axis movement is stronger - go forward
      ROBOT_FORWARD();
    } else {
      // X-axis movement is stronger - go left
      ROBOT_LEFT();
    }
  } else {
    stop();
  }
}
```

Similar logic is implemented for `forward_right`, `backward_left`, and `backward_right` functions.

## Control Flow

### Joystick Control Mode

1. Read joystick direction and X/Y values
2. Determine the direction based on joystick position
3. Call the appropriate movement function:
   - For cardinal directions: `forward()`, `backward()`, `left()`, or `right()`
   - For diagonal directions: `forward_left()`, `forward_right()`, `backward_left()`, or `backward_right()`
4. The movement function checks for obstacles and chooses the appropriate motor actions

### Voice Control Mode

1. Recognize voice command
2. Map command to appropriate joystick values:
   - "Forward" → (512, 0)
   - "Backward" → (512, 1023)
   - "Left" → (0, 512)
   - "Right" → (1023, 512)
   - "Stop" → No action
3. Call the corresponding movement function
4. The movement function checks for obstacles and chooses the appropriate motor actions

## Safety Features

1. **Collision Prevention**:
   - Front ultrasonic sensor prevents forward movement when obstacles are detected
   - Back ultrasonic sensor prevents backward movement when obstacles are detected
   - Minimum accepted distance is defined as 30 units

2. **Emergency Stop**:
   - The robot can be stopped via joystick center position or "stop" voice command

## Mode Switching

The user can switch between joystick control mode and voice control mode by pressing the joystick button:
- Single press toggles between modes
- The system remembers the current mode until changed

## Technical Implementation Notes

1. **Joystick Calibration**:
   - Center position: X=512, Y=512
   - X-axis: 0 (left) to 1023 (right)
   - Y-axis: 0 (up) to 1023 (down)

2. **Motor Control**:
   - Motor 1: Pins 14, 15
   - Motor 2: Pins 16, 17
   - HIGH/LOW combinations determine direction

3. **Mixed Direction Logic**:
   - The system compares the absolute distance from center in both axes
   - This approach provides more intuitive control than fixed thresholds
   - The robot always chooses a pure direction rather than attempting diagonal movement

## Debugging Features

The system includes several debugging functions that can be uncommented for troubleshooting:
- `log_joystick_info()`: Displays joystick position and direction
- `log_ultrasonic_info()`: Shows distances from front and back sensors
- `log_voice_module_info()`: Displays recognized voice commands

## Conclusion

This robot control system provides an intuitive and safe way to control the robot using either joystick or voice commands. The mixed direction control logic ensures that the robot always moves in the most appropriate direction based on user input, while the safety features prevent collisions with obstacles.
