#ifndef MAIN_H
#define MAIN_H

#include <Arduino.h>
#include <SoftwareSerial.h>
#include "error_state.h"


#include "joystick.h"
#include "VoiceRecognitionV3.h"
#include "voice_module.h"
#include "led.h"

// for both altrasonic
#define MINIMUM_ACCEPTED_DISTANCE     30

// Relay Module Pin Definitions
#define RELAY1_PIN1     14  // Motor 1 control pin 1
#define RELAY1_PIN2     15  // Motor 1 control pin 2
#define RELAY2_PIN1     16  // Motor 2 control pin 1
#define RELAY2_PIN2     17  // Motor 2 control pin 2

typedef enum{
  CONTROL_BY_JOYSTICK,
  CONTROL_BY_VOICE,
  CONTROL_BY_BLUETOOTH
}mode_t;

// 


// Bluetooth control function declarations
void bluetooth_init();
bool process_bluetooth_commands();
void process_remote_command(char command);
void process_voice_command(char command);
// void check_obstacles_while_moving();
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