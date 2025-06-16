#ifndef MAIN_H
#define MAIN_H

#include <Arduino.h>
#include <SoftwareSerial.h>
#include "error_state.h"


#include "joystick.h"
#include "ultrasonic.h"
#include "VoiceRecognitionV3.h"
#include "voice_module.h"
#include "led.h"

// for both altrasonic
#define MINIMUM_ACCEPTED_DISTANCE     30


typedef enum{
  CONTROL_BY_JOYSTICK,
  CONTROL_BY_VOICE,
  CONTROL_BY_BLUETOOTH
}mode_t;

// 
 extern int back_dist, front_dist;


// Bluetooth control function declarations
void bluetooth_init();
bool process_bluetooth_commands();
void process_remote_command(char command);
void process_voice_command(char command);
void check_obstacles_while_moving();
bool motor_is_moving_forward();
bool motor_is_moving_backward();

// Motot

// Motor control function prototypes
void motor_1_forward();
void motor_1_backward();
void motor_1_off();
void motor_2_forward();
void motor_2_backward();
void motor_2_off();

// Robot movement function prototypes
void ROBOT_FORWARD();
void ROBOT_BACKWARD();
void ROBOT_LEFT();
void ROBOT_RIGHT();
void ROBOT_STOP();

#endif