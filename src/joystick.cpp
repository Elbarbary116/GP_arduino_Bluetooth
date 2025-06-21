#include <Arduino.h>
#include "error_state.h"
#include "joystick.h"

// Increased deadzone to prevent unwanted movements
#define IMPROVED_JOYSTICK_DEADZONE 100

static uint8_t joystick_process_sw_button_value(uint8_t sw_ptn_value);

void joystick_init() {
  pinMode(JOYSTICK_X_PIN, INPUT);
  pinMode(JOYSTICK_Y_PIN, INPUT);
  pinMode(JOYSTICK_SW_PIN, INPUT_PULLUP);
  
  // Give joystick time to stabilize
  delay(200);
  
  // Read initial values to calibrate
  int x = analogRead(JOYSTICK_X_PIN);
  int y = analogRead(JOYSTICK_Y_PIN);
  
  Serial.print("Joystick initialized. Initial values - X: ");
  Serial.print(x);
  Serial.print(", Y: ");
  Serial.println(y);
}

int joystick_read_x() {
  // Read multiple times and average to reduce noise
  int sum = 0;
  for (int i = 0; i < 5; i++) {
    sum += analogRead(JOYSTICK_X_PIN);
    delay(5);
  }
  return sum / 5;
}

int joystick_read_y() {
  // Read multiple times and average to reduce noise
  int sum = 0;
  for (int i = 0; i < 5; i++) {
    sum += analogRead(JOYSTICK_Y_PIN);
    delay(5);
  }
  return sum / 5;
}

button_state_t joystick_get_sw_button_value(){
  return (button_state_t)(joystick_process_sw_button_value(!digitalRead(JOYSTICK_SW_PIN)));
}

static uint8_t joystick_process_sw_button_value(uint8_t sw_ptn_value)
{
  static button_state_t btn_sm_state = NOT_PRESSED;
  static uint32_t curr_time = millis();

  switch(btn_sm_state){

    case NOT_PRESSED:

      if(sw_ptn_value){
        btn_sm_state = BOUNCE;
        curr_time = millis();
      }
      break;
  
    case BOUNCE:

      if(millis() - curr_time >= DEBOUNCE_DELAY_MS){
        //50ms has passed 
        if(sw_ptn_value){
          btn_sm_state = PRESSED;
          return sw_ptn_value;
        }
        else
          btn_sm_state = NOT_PRESSED;
      }
      break;
  
    case PRESSED:
      if(!sw_ptn_value){
        btn_sm_state = BOUNCE;
        curr_time = millis();
      }
      break;
  }

  return 0;
}

JoystickDirection joystick_get_direction() {
  // Use the improved deadzone for more stable readings
  int x = joystick_read_x();
  int y = joystick_read_y();
  
  // Apply larger deadzone to prevent unwanted movements
  if (abs(x - 512) < IMPROVED_JOYSTICK_DEADZONE && abs(y - 512) < IMPROVED_JOYSTICK_DEADZONE) {
    return DIR_CENTER;
  }

  bool up =    y < (512 - IMPROVED_JOYSTICK_DEADZONE);
  bool down =  y > (512 + IMPROVED_JOYSTICK_DEADZONE);
  bool left =  x < (512 - IMPROVED_JOYSTICK_DEADZONE);
  bool right = x > (512 + IMPROVED_JOYSTICK_DEADZONE);
  
  // Apply more strict thresholds for diagonal directions
  if (up && left && abs(x - 512) > 100 && abs(y - 512) > 100) return DIR_UP_LEFT;
  if (up && right && abs(x - 512) > 100 && abs(y - 512) > 100) return DIR_UP_RIGHT;
  if (down && left && abs(x - 512) > 100 && abs(y - 512) > 100) return DIR_DOWN_LEFT;
  if (down && right && abs(x - 512) > 100 && abs(y - 512) > 100) return DIR_DOWN_RIGHT;
  
  // For cardinal directions, use the improved deadzone
  if (up) return DIR_UP;
  if (down) return DIR_DOWN;
  if (left) return DIR_LEFT;
  if (right) return DIR_RIGHT;
  
  // Default to center if no clear direction
  return DIR_CENTER;
}

bool joystick_is_centered() {
  int x = joystick_read_x();
  int y = joystick_read_y();
  
  // Use the improved deadzone for more stable center detection
  if (abs(x - 512) < IMPROVED_JOYSTICK_DEADZONE && abs(y - 512) < IMPROVED_JOYSTICK_DEADZONE) {
    return true;
  }
  else return false;
}

