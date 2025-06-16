
#include <Arduino.h>
#include "led.h"


Led::Led(int pin) : led_pin(pin) 
{
  pinMode(led_pin, OUTPUT);
}


void Led::on(){
  digitalWrite(led_pin, HIGH);
}


void Led::off(){
  digitalWrite(led_pin, LOW);
}