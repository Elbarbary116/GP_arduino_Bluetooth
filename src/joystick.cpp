#include <Arduino.h>
#include "error_state.h"
#include "joystick.h"


static uint8_t joystick_process_sw_button_value(uint8_t sw_ptn_value);


void joystick_init() {
  pinMode(JOYSTICK_X_PIN, INPUT);
  pinMode(JOYSTICK_Y_PIN, INPUT);
  pinMode(JOYSTICK_SW_PIN, INPUT_PULLUP);
}



int joystick_read_x() {
  return analogRead(JOYSTICK_X_PIN);
}



int joystick_read_y() {
  return analogRead(JOYSTICK_Y_PIN);
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

      if(millis() - curr_time >= 50 ){
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

  int x = analogRead(JOYSTICK_X_PIN);
  int y = analogRead(JOYSTICK_Y_PIN);
  
  if (abs(x - 512) < JOYSTICK_DEADZONE && abs(y - 512) < JOYSTICK_DEADZONE) {
    return DIR_CENTER;
  }


  bool up =    y < (512 - JOYSTICK_DEADZONE);
  bool down =  y > (512 + JOYSTICK_DEADZONE);
  bool left =  x < (512 - JOYSTICK_DEADZONE);
  bool right = x > (512 + JOYSTICK_DEADZONE);
  
  if (up && left) return DIR_UP_LEFT;
  if (up && right) return DIR_UP_RIGHT;
  if (down && left) return DIR_DOWN_LEFT;
  if (down && right) return DIR_DOWN_RIGHT;
  if (up) return DIR_UP;
  if (down) return DIR_DOWN;
  if (left) return DIR_LEFT;
  if (right) return DIR_RIGHT;

}


bool joystick_is_centered() {
  int x = analogRead(JOYSTICK_X_PIN);
  int y = analogRead(JOYSTICK_Y_PIN);
  
  if (abs(x - 512) < JOYSTICK_DEADZONE && abs(y - 512) < JOYSTICK_DEADZONE) {
    return true;
  }
  else return false;
}

