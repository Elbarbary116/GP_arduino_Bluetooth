#include "main.h"

/********************** Joystick ***************/
JoystickDirection dir;
int joystic_x_value, joystic_y_value;
int counter;

/********************** Ultrasonic ***************/
Ultrasonic front_ultrasonic(7, 6); //trig-> 7,  echo-> 6
Ultrasonic back_utrasonic(9, 8);  //trig-> 9,  echo-> 8
 int back_dist, front_dist;

/********************** Main application mode ***************/
mode_t main_mode = CONTROL_BY_BLUETOOTH; // start with that mode


/********************** Leds ***************/
Led led_forward(14), led_backward(15), led_left(16), led_right(17);


/********************** Voice module ***************/
int rec = STOP;

// remove Led and replace the code of it as relay module 2 channel
// which will be connected to 2 motors
// motor 1: 14, 15
// motor 2: 16, 17
// replace the code of led with relay module 2 channel


void motor_1_forward(){
  digitalWrite(14, HIGH); 
  digitalWrite(15, LOW);
}

void motor_1_backward(){
  digitalWrite(14, LOW); 
  digitalWrite(15, HIGH);
}

void motor_1_off(){
  digitalWrite(14, LOW);
  digitalWrite(15, LOW);
}


void motor_2_forward(){
  digitalWrite(16, HIGH);
  digitalWrite(17, LOW);
}

void motor_2_backward(){
  digitalWrite(16, LOW);
  digitalWrite(17, HIGH);
}

void motor_2_off(){
  digitalWrite(16, LOW);
  digitalWrite(17, LOW);
}


void ROBOT_FORWARD(){
  motor_1_forward();
  motor_2_forward();
}

void ROBOT_BACKWARD(){
  motor_1_backward();
  motor_2_backward();
}

void ROBOT_LEFT(){
  motor_1_backward();
  motor_2_forward();
}

void ROBOT_RIGHT(){
  motor_1_forward();
  motor_2_backward();
}

void ROBOT_STOP(){
  motor_1_off();
  motor_2_off();
}



void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  joystick_init();

  if (voice_module_init() == ES_OK){
    //Serial.println("voice module is ready ... ");
  }

  // Initialize Bluetooth communication
  bluetooth_init();
  
  //Serial.println("joystick mode on ... "); 
}

void loop() {
  

  // ###############################################
  // ###############################################
  // #########    control the mode      ############
  // ###############################################
  
  // read the push button value
  button_state_t user_button = joystick_get_sw_button_value();


  if(user_button == PRESSED){
    //User button action

    if(main_mode == CONTROL_BY_JOYSTICK){
      main_mode = CONTROL_BY_VOICE;
      Serial.println("voice mode on");
      ROBOT_STOP();
      rec = STOP;
    }

    else if(main_mode == CONTROL_BY_VOICE) {
      main_mode = CONTROL_BY_BLUETOOTH;
      Serial.println("bluetooth mode on");
      ROBOT_STOP();
      rec = STOP;
    }
    else {
      main_mode = CONTROL_BY_JOYSTICK;
      Serial.println("joystick mode on");
      ROBOT_STOP();
      rec = STOP;
    }
    delay(200); // Debounce delay
    // Wait for button release
    while(joystick_get_sw_button_value() == PRESSED) {
      delay(10);
    }
  }



  // ###############################################
  // ###############################################
  // #########    red the ultrasonic    ############
  // ###############################################

  front_dist = front_ultrasonic.get_distance();
  back_dist = back_utrasonic.get_distance();



  // ###############################################
  // ###############################################
  // #########   control based on mode  ############
  // ###############################################
  
  if(main_mode == CONTROL_BY_JOYSTICK){

    // 1. get joytic direction
    dir = joystick_get_direction();

    // get x and y values for speed control
    joystic_x_value = joystick_read_x();
    joystic_y_value = joystick_read_y();


    switch (dir) {
      case DIR_CENTER:
      // STOP
      stop();
      break;

      case DIR_UP:
      // FORWARD
      forward(joystic_x_value, joystic_y_value);
      break;

      case DIR_DOWN:
      // BACKWARD
      backward(joystic_x_value, joystic_y_value);
      break;

      case DIR_LEFT:
      // LEFT
      left(joystic_x_value, joystic_y_value);
      break;

      case DIR_RIGHT:
      // RIGHT
      right(joystic_x_value, joystic_y_value);
      break;

      case DIR_UP_LEFT:
      // FORWARD AND LEFT
      forward_left(joystic_x_value, joystic_y_value);
      break;

      case DIR_UP_RIGHT:
      // FORWARD AND RIGHT
      forward_right(joystic_x_value, joystic_y_value);
      break;

      case DIR_DOWN_LEFT:
      // BACKWARD AND LEFT
      backward_left(joystic_x_value, joystic_y_value);
      break;

      case DIR_DOWN_RIGHT:
      // BACKWARD AND RIGHT
      backward_right(joystic_x_value, joystic_y_value);
      break;
    }


    //log_joystick_info();

  }
  else if(main_mode == CONTROL_BY_VOICE){

    rec = voice_module_recognize();

    switch(rec){
      case FORWARD:
      forward(512, 0);
      break;

      case BACKWARD:
      backward(512, 1023);
      break;
      
      case STOP:
      stop();
      break;
      
      case LEFT:
      left(0, 512);
      break;
      
      case RIGHT:
      right(1023, 512);
      break;

      default:
     // Serial.println("Record function undefined");
      break;
    }

  }
  else if(main_mode == CONTROL_BY_BLUETOOTH) {
    // Process any Bluetooth commands
    process_bluetooth_commands();
    // Serial.println("bluetooth mode on");
    
    // Continuously check for obstacles while moving
    check_obstacles_while_moving();
  } 

  //dir = joystick_get_direction();
  //log_joystick_info();
  //log_ultrasonic_info();
  //log_voice_module_info();

  //delay(100);
}

void stop() {
  // led_forward.off();
  // led_backward.off();
  // led_left.off();

  // led_right.off();
  ROBOT_STOP();
}

void forward(int x_val, int y_val) {

  if (front_dist > MINIMUM_ACCEPTED_DISTANCE) {
    // led_forward.on();
    // led_backward.off();
    // led_left.off();
    // led_right.off();
    ROBOT_FORWARD();
  } else {
    stop();
  }
  
  (void)x_val;
  (void)y_val;
}

void forward_left(int x_val, int y_val) {

  if (front_dist > MINIMUM_ACCEPTED_DISTANCE) {
    // led_forward.on();
    // led_backward.off();
    // led_left.on();
    // led_right.off();
    
    // Calculate how far the joystick is from center in each direction
    int x_distance_from_center = abs(x_val - 512);
    int y_distance_from_center = abs(y_val - 512);
    
    // Compare the distances to determine which direction is stronger
    if (y_distance_from_center > x_distance_from_center) {
      // Y-axis movement is stronger - go forward
      ROBOT_FORWARD();
    } else {
      // X-axis movement is stronger - go left
      ROBOT_LEFT();
    }
   
  } else {
    stop();
  }
}


void forward_right(int x_val, int y_val) {

  if (front_dist > MINIMUM_ACCEPTED_DISTANCE) {
    // led_forward.on();
    // led_backward.off();
    // led_left.off();
    // led_right.on();
    
    // Calculate how far the joystick is from center in each direction
    int x_distance_from_center = abs(x_val - 512);
    int y_distance_from_center = abs(y_val - 512);
    
    // Compare the distances to determine which direction is stronger
    if (y_distance_from_center > x_distance_from_center) {
      // Y-axis movement is stronger - go forward
      ROBOT_FORWARD();
    } else {
      // X-axis movement is stronger - go right
      ROBOT_RIGHT();
    }
    
  } else {
    stop();
  }
}


void backward(int x_val, int y_val) {

  if (back_dist > MINIMUM_ACCEPTED_DISTANCE) {
    // led_forward.off();
    // led_backward.on();
    // led_left.off();
    // led_right.off();
    ROBOT_BACKWARD();
    
  } else {
    stop();
  }

  (void)x_val;
  (void)y_val;
}

void backward_left(int x_val, int y_val) {

  if (back_dist > MINIMUM_ACCEPTED_DISTANCE) {
    // led_forward.off();
    // led_backward.on();
    // led_left.on();
    // led_right.off();
    
    // Calculate how far the joystick is from center in each direction
    int x_distance_from_center = abs(x_val - 512);
    int y_distance_from_center = abs(y_val - 512);
    
    // Compare the distances to determine which direction is stronger
    if (y_distance_from_center > x_distance_from_center) {
      // Y-axis movement is stronger - go backward
      ROBOT_BACKWARD();
    } else {
      // X-axis movement is stronger - go left
      ROBOT_LEFT();
    }
   
  } else {
    stop();
  }
}

void backward_right(int x_val, int y_val) {

  if (back_dist > MINIMUM_ACCEPTED_DISTANCE) {
    // led_forward.off();
    // led_backward.on();
    // led_left.off();
    // led_right.on();
    
    // Calculate how far the joystick is from center in each direction
    int x_distance_from_center = abs(x_val - 512);
    int y_distance_from_center = abs(y_val - 512);
    
    // Compare the distances to determine which direction is stronger
    if (y_distance_from_center > x_distance_from_center) {
      // Y-axis movement is stronger - go backward
      ROBOT_BACKWARD();
    } else {
      // X-axis movement is stronger - go right
      ROBOT_RIGHT();
    }
  } else {
    stop();
  }
}

void left(int x_val, int y_val) {

  // led_forward.off();
  // led_backward.off();
  // led_left.on();
  // led_right.off();

  ROBOT_LEFT();
  
  (void)x_val;
  (void)y_val;
}

void right(int x_val, int y_val) {

    // led_forward.off();
    // led_backward.off();
    // led_left.off();
    // led_right.on();
    ROBOT_RIGHT();
  
  (void)x_val;
  (void)y_val;
}


void log_ultrasonic_info(){
  Serial.print("front distance: ");
  Serial.println(front_ultrasonic.get_distance());


  Serial.print("back distance: ");
  Serial.println(back_utrasonic.get_distance());
}



void log_joystick_info() {
  Serial.print("X: ");
  Serial.println(joystick_read_x());

  Serial.print("Y: ");
  Serial.println(joystick_read_y());

  Serial.print("counter: ");
  Serial.println(counter);


  if (joystick_is_centered()){
    Serial.print("crnter: ");
    Serial.println("True");
  }
  else {
    Serial.print("crnter: ");
    Serial.println("False");
  }
  
  switch(dir) {
    case DIR_CENTER:     Serial.println("Center");     break;
    case DIR_UP:         Serial.println("Up");        break;
    case DIR_DOWN:       Serial.println("Down");      break;
    case DIR_LEFT:       Serial.println("Left");      break;
    case DIR_RIGHT:      Serial.println("Right");     break;
    case DIR_UP_LEFT:    Serial.println("Up-Left");   break;
    case DIR_UP_RIGHT:   Serial.println("Up-Right");  break;
    case DIR_DOWN_LEFT:  Serial.println("Down-Left"); break;
    case DIR_DOWN_RIGHT: Serial.println("Down-Right");break;
    default:             Serial.println("Unknown");   break;
  }

}


void log_voice_module_info(){

  rec = voice_module_recognize();

  switch(rec){
    case FORWARD:
      Serial.println(" forward ");
      break;

    case BACKWARD:
      Serial.println(" backward ");
      break;
    
    case STOP:
      Serial.println(" stop ");
      break;
    
    case LEFT:
      Serial.println(" left ");
      break;
    
    case RIGHT:
      Serial.println(" right ");
      break;

    default:
      Serial.println("Record function undefined");
      break;
    }
}

JoystickDirection get_joystick_direction_from_values(int x_val, int y_val) {
  if (x_val < 256 && y_val < 256) {
    return DIR_UP_LEFT;
  } else if (x_val > 768 && y_val < 256) {
    return DIR_UP_RIGHT;
  } else if (x_val < 256 && y_val > 768) {
    return DIR_DOWN_LEFT;
  } else if (x_val > 768 && y_val > 768) {
    return DIR_DOWN_RIGHT;
  } else if (y_val < 256) {
    return DIR_UP;
  } else if (y_val > 768) {
    return DIR_DOWN;
  } else if (x_val < 256) {
    return DIR_LEFT;
  } else if (x_val > 768) {
    return DIR_RIGHT;
  } else {
    return DIR_CENTER;
  }
}

