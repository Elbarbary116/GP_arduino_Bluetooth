# Ultrasonic Module Documentation (ultrasonic.cpp & ultrasonic.h)

## Overview
This module provides an interface for using ultrasonic distance sensors with the robot. It encapsulates sensor initialization, distance measurement, and timeout handling.

---

## ultrasonic.h
### Purpose
- Defines the `Ultrasonic` class for managing ultrasonic sensors.

### Class Interface
- **Constructor**: `Ultrasonic(int trig, int echo)` — Sets up the trigger and echo pins.
- **Method**: `int get_distance()` — Returns the measured distance in centimeters, or -1 if no echo is received (timeout).

### Members
- `int trig_pin`: Trigger pin.
- `int echo_pin`: Echo pin.
- `unsigned long timeout`: Maximum time to wait for an echo (in microseconds).

---

## ultrasonic.cpp
### Purpose
- Implements the `Ultrasonic` class methods.
- Handles sensor initialization and distance measurement logic.

### Key Functions
- `Ultrasonic::Ultrasonic(int trig, int echo)`: Initializes the sensor pins.
- `Ultrasonic::get_distance()`: Sends a trigger pulse, measures echo duration, and calculates distance using the speed of sound.

### Measurement Details
- Sends a 10µs pulse on the trigger pin.
- Measures the time for the echo pin to go HIGH.
- Calculates distance: `distance (cm) = duration (µs) * 0.0343 / 2`
- Returns -1 if no echo is received within the timeout.

---

## Integration
- Used by `main.ino` and `bluetooth_control.cpp` for obstacle detection and avoidance.
- Designed to be modular and reusable for multiple sensors.

## Notes
- Timeout can be adjusted for different sensor ranges.
- The class is suitable for HC-SR04 and similar ultrasonic sensors. 