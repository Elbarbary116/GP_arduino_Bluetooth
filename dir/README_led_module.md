# LED Module Documentation (led.cpp & led.h)

## Overview
This module provides a simple interface for controlling LEDs (or relays) on the robot. It encapsulates pin initialization and basic on/off control.

---

## led.h
### Purpose
- Defines the `Led` class for managing an LED or relay output.

### Class Interface
- **Constructor**: `Led(int pin)` — Sets up the pin as an output.
- **Methods**:
  - `void on()`: Turns the LED/relay on (sets pin HIGH).
  - `void off()`: Turns the LED/relay off (sets pin LOW).

### Members
- `int led_pin`: The pin number connected to the LED or relay.

---

## led.cpp
### Purpose
- Implements the `Led` class methods.
- Handles pin initialization and on/off logic.

### Key Functions
- `Led::Led(int pin)`: Initializes the pin as OUTPUT.
- `Led::on()`: Sets the pin HIGH.
- `Led::off()`: Sets the pin LOW.

---

## Integration
- Used by `main.ino` to indicate movement direction or control relays for motors.
- Designed to be modular and reusable for multiple outputs.

## Notes
- The class can be used for both LEDs and relay modules.
- Simple and efficient for basic output control. 