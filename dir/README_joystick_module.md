# Joystick Module Documentation (joystick.cpp & joystick.h)

## Overview
This module provides an interface for reading and debouncing a joystick with X, Y, and button (SW) inputs. It supports direction detection, analog value reading, and button state management.

---

## joystick.h
### Purpose
- Defines the `JoystickDirection` enum and `button_state_t` enum for direction and button state management.
- Declares function prototypes for joystick initialization, reading, and direction detection.
- Defines pin assignments and deadzone constants.

### Key Definitions
- **Pin Macros**: `JOYSTICK_X_PIN`, `JOYSTICK_Y_PIN`, `JOYSTICK_SW_PIN`
- **Enums**:
  - `button_state_t`: `NOT_PRESSED`, `PRESSED`, `BOUNCE`
  - `JoystickDirection`: `DIR_CENTER`, `DIR_UP`, `DIR_DOWN`, etc.
- **Function Prototypes**:
  - `void joystick_init()`
  - `int joystick_read_x()`
  - `int joystick_read_y()`
  - `button_state_t joystick_get_sw_button_value()`
  - `bool joystick_is_centered()`
  - `JoystickDirection joystick_get_direction()`

---

## joystick.cpp
### Purpose
- Implements the joystick reading, debouncing, and direction detection logic.

### Key Functions
- `joystick_init()`: Initializes the joystick pins.
- `joystick_read_x()`, `joystick_read_y()`: Reads analog values from the joystick axes.
- `joystick_get_sw_button_value()`: Returns the debounced state of the joystick button.
- `joystick_get_direction()`: Determines the joystick's direction based on analog values and deadzone.
- `joystick_is_centered()`: Checks if the joystick is in the center position.

### Debouncing
- Uses a simple state machine to debounce the button input.
- `DEBOUNCE_DELAY_MS` can be adjusted for different hardware.

---

## Integration
- Used by `main.ino` for manual control and mode switching.
- Designed to be modular and reusable for other input devices.

## Notes
- The module is robust for both analog and digital joystick inputs.
- Can be extended for more complex input handling if needed. 