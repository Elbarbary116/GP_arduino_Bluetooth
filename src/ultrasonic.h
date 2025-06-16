#ifndef ULTRASONIC_H
#define ULTRASONIC_H


class Ultrasonic{
  
public:

  Ultrasonic(int trig, int echo);
  int get_distance();

private:

  int trig_pin;
  int echo_pin;
  unsigned long timeout = 20000;   // Default timeout (µs)
};

#endif