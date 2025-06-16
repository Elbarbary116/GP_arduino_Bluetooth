#include <Arduino.h>
#include "error_state.h"
#include "ultrasonic.h"

Ultrasonic::Ultrasonic(int trig, int echo){
  trig_pin = trig;
  echo_pin = echo;


  pinMode(trig_pin, OUTPUT);
  pinMode(echo_pin, INPUT);
  digitalWrite(trig_pin, LOW);
}


int Ultrasonic::get_distance(){
  // Send 10µs pulse
  digitalWrite(trig_pin, LOW);
  delayMicroseconds(2);
  digitalWrite(trig_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_pin, LOW);

  // Measure echo pulse duration
  unsigned long duration = pulseIn(echo_pin, HIGH, timeout);

  // Convert to distance (cm)
  // Speed of sound: 343m/s = 0.0343cm/µs
  // Divide by 2 for round trip
  return (duration == 0) ? -1 : duration * 0.0343 / 2;
}