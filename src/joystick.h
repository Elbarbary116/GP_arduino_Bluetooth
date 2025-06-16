#ifndef JOYSTICK_H
#define JOYSTICK_H

// Pin connection macros
#define JOYSTICK_X_PIN        A4    // Analog pin for X-axis [0    512    1023]
#define JOYSTICK_Y_PIN        A5    // Analog pin for Y-axis [0    512    1023]
#define JOYSTICK_SW_PIN       2    // Digital pin for switch/button


// Deadzone to account for joystick not perfectly centered
#define JOYSTICK_DEADZONE 20

// Button states
typedef enum {
  NOT_PRESSED,
  PRESSED,
  BOUNCE
}button_state_t;

// Debounce constants
#define DEBOUNCE_DELAY_MS    50  // Adjust as needed (typically 10-100ms)


// Direction enumeration
typedef enum {
  DIR_CENTER,
  DIR_UP,
  DIR_DOWN,
  DIR_LEFT,
  DIR_RIGHT,
  DIR_UP_LEFT,
  DIR_UP_RIGHT,
  DIR_DOWN_LEFT,
  DIR_DOWN_RIGHT
} JoystickDirection;


// Function prototypes
void joystick_init();
int joystick_read_x();
int joystick_read_y();
button_state_t joystick_get_sw_button_value();

bool joystick_is_centered();
JoystickDirection joystick_get_direction();


#endif