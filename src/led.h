#ifndef LED_H
#define LED_H


class Led{

public:

  Led(int pin);
  void on();
  void off();

private:
  int led_pin;
};

#endif