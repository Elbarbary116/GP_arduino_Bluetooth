#include <Arduino.h>
#include "main.h"
/********************** Joystick ***************/
JoystickDirection dir;
int joystic_x_value, joystic_y_value;
int counter;

/********************** Ultrasonic ***************/
// Ultrasonic front_ultrasonic(7, 6); //trig-> 7,  echo-> 6
// Ultrasonic back_ultrasonic(9, 8);  //trig-> 9,  echo-> 8
// int back_dist, front_dist;

/********************** Main application mode ***************/
mode_t main_mode = CONTROL_BY_BLUETOOTH; // start with that mode


/********************** Leds ***************/
// Led led_forward(14), led_backward(15), led_left(16), led_right(17);




/********************** Voice module ***************/
int rec = STOP;

// Flag to prevent rapid movement changes
unsigned long lastDirectionChangeTime = 0;
const unsigned long directionChangeDelay = 250; // Increased from 150ms to 250ms for more stable control

// Track current motor states to prevent unnecessary relay switching
bool motor1_is_forward = false;
bool motor1_is_backward = false;
bool motor2_is_forward = false;
bool motor2_is_backward = false;

// remove Led and replace the code of it as relay module 2 channel
// which will be connected to 2 motors
// motor 1: 14, 15
// motor 2: 16, 17
// replace the code of led with relay module 2 channel

// Motor control functions for 2-channel relay module
// For relay modules, typically LOW activates the relay and HIGH deactivates it
// Adjust the logic based on your specific relay module if needed

void motor_1_forward(){
  // Only change state if needed
  if (!motor1_is_forward) {
    Serial.println("Setting Motor 1 to FORWARD");
    // Turn off backward first if it's on
    if (motor1_is_backward) {
      Serial.println("  - Turning off backward first");
      digitalWrite(RELAY1_PIN2, LOW);
      motor1_is_backward = false;
      delay(20); // Small delay between relay operations
    }
    digitalWrite(RELAY1_PIN1, HIGH); 
    // digitalWrite(RELAY1_PIN2, LOW); // Ensure the other pin is LOW
    motor1_is_forward = true;
    Serial.println("  - Motor 1 now in FORWARD state");
  }
}

void motor_1_backward(){
  // Only change state if needed
  if (!motor1_is_backward) {
    Serial.println("Setting Motor 1 to BACKWARD");
    // Turn off forward first if it's on
    if (motor1_is_forward) {
      Serial.println("  - Turning off forward first");
      digitalWrite(RELAY1_PIN1, LOW);
      motor1_is_forward = false;
      delay(20); // Small delay between relay operations
    }
    
    // First ensure RELAY1_PIN1 is LOW to prevent shorts
    // digitalWrite(RELAY1_PIN1, LOW);
    // delay(20); // Small delay for safety
    
    // Then set RELAY1_PIN2 HIGH - this sequence is important
    digitalWrite(RELAY1_PIN2, HIGH);
    motor1_is_backward = true;
    Serial.println("  - Motor 1 now in BACKWARD state");
  }
}

void motor_1_off(){
  // Only change state if needed
  if (motor1_is_forward || motor1_is_backward) {
    Serial.println("Stopping Motor 1");
    digitalWrite(RELAY1_PIN1, LOW);
    digitalWrite(RELAY1_PIN2, LOW);
    motor1_is_forward = false;
    motor1_is_backward = false;
    delay(20); // Small delay to ensure relays have time to switch
    Serial.println("  - Motor 1 now STOPPED");
  }
}

void motor_2_forward(){
  // Only change state if needed
  if (!motor2_is_forward) {
    Serial.println("Setting Motor 2 to FORWARD");
    // Turn off backward first if it's on
    if (motor2_is_backward) {
      Serial.println("  - Turning off backward first");
      digitalWrite(RELAY2_PIN2, LOW);
      motor2_is_backward = false;
      delay(20); // Small delay between relay operations
    }
    digitalWrite(RELAY2_PIN1, HIGH);
    // digitalWrite(RELAY2_PIN2, LOW); // Ensure the other pin is LOW
    motor2_is_forward = true;
    Serial.println("  - Motor 2 now in FORWARD state");
  }
}

void motor_2_backward(){
  // Only change state if needed
  if (!motor2_is_backward) {
    Serial.println("Setting Motor 2 to BACKWARD");
    // Turn off forward first if it's on
    if (motor2_is_forward) {
      Serial.println("  - Turning off forward first");
      digitalWrite(RELAY2_PIN1, LOW);
      motor2_is_forward = false;
      delay(20); // Small delay between relay operations
    }
    
    // First ensure RELAY2_PIN1 is LOW to prevent shorts
    // digitalWrite(RELAY2_PIN1, LOW);
    // delay(20); // Small delay for safety
    
    // Then set RELAY2_PIN2 HIGH - this sequence is important
    digitalWrite(RELAY2_PIN2, HIGH);
    motor2_is_backward = true;
    Serial.println("  - Motor 2 now in BACKWARD state");
  }
}

void motor_2_off(){
  // Only change state if needed
  if (motor2_is_forward || motor2_is_backward) {
    Serial.println("Stopping Motor 2");
    digitalWrite(RELAY2_PIN1, LOW);
    digitalWrite(RELAY2_PIN2, LOW);
    motor2_is_forward = false;
    motor2_is_backward = false;
    delay(20); // Small delay to ensure relays have time to switch
    Serial.println("  - Motor 2 now STOPPED");
  }
}

// Robot movement functions - optimized for continuous movement
void ROBOT_FORWARD(){
  Serial.println("\n>> ROBOT MOVING FORWARD");
  
  // Then activate forward movement
  Serial.println("  - Setting motors for FORWARD movement");
  motor_1_forward();
  motor_2_forward();
  
  Serial.println("  - FORWARD movement state set");
}

void ROBOT_BACKWARD(){
  Serial.println("\n>> ROBOT MOVING BACKWARD");
  
  // Then activate backward movement
  Serial.println("  - Setting motors for BACKWARD movement");
  motor_1_backward();
  motor_2_backward();
  
  Serial.println("  - BACKWARD movement state set");
}

void ROBOT_LEFT(){
  Serial.println("\n>> ROBOT TURNING LEFT");
  
  // For LEFT: Motor 1 backward, Motor 2 forward
  // This sequence is important for reliable operation
  Serial.println("  - Setting motors for LEFT turn");
  motor_1_backward();
  motor_2_forward();
  
  Serial.println("  - LEFT turn state set");
}

void ROBOT_RIGHT(){
  Serial.println("\n>> ROBOT TURNING RIGHT");
  
  // For RIGHT: Motor 1 forward, Motor 2 backward
  // This sequence is important for reliable operation
  Serial.println("  - Setting motors for RIGHT turn");
  motor_1_forward();
  motor_2_backward();
  
  Serial.println("  - RIGHT turn state set");
}

void ROBOT_STOP(){
  Serial.println("\n>> ROBOT STOPPING");
  motor_1_off();
  motor_2_off();
}

// Add these variables at the top with other global variables
unsigned long lastDirectionPrintTime = 0;
const unsigned long directionPrintInterval = 1000; // Print direction every 1 second

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  // Initialize relay pins as outputs
  pinMode(RELAY1_PIN1, OUTPUT);
  pinMode(RELAY1_PIN2, OUTPUT);
  pinMode(RELAY2_PIN1, OUTPUT);
  pinMode(RELAY2_PIN2, OUTPUT);
  
  // Initialize all relay pins to LOW (relays off)
  digitalWrite(RELAY1_PIN1, LOW);
  digitalWrite(RELAY1_PIN2, LOW);
  digitalWrite(RELAY2_PIN1, LOW);
  digitalWrite(RELAY2_PIN2, LOW);

  // Initialize motor state trackers
  motor1_is_forward = false;
  motor1_is_backward = false;
  motor2_is_forward = false;
  motor2_is_backward = false;

  // Initialize joystick
  joystick_init();

  if (voice_module_init() == ES_OK){
    Serial.println("Voice module is ready");
  } else {
    Serial.println("Voice module initialization failed");
  }

  // Initialize Bluetooth communication
  bluetooth_init();
  
  Serial.println("System initialized. Bluetooth mode active."); 
  
  // Ensure motors are stopped at startup
  ROBOT_STOP();
  delay(500);
}

// Function to check if enough time has passed to change direction
bool canChangeDirection() {
  unsigned long currentTime = millis();
  if (currentTime - lastDirectionChangeTime >= directionChangeDelay) {
    lastDirectionChangeTime = currentTime;
    return true;
  }
  return false;
}

// Add this function before the loop function
void print_current_direction() {
  // Get the current pin states
  int r1p1 = digitalRead(RELAY1_PIN1);
  int r1p2 = digitalRead(RELAY1_PIN2);
  int r2p1 = digitalRead(RELAY2_PIN1);
  int r2p2 = digitalRead(RELAY2_PIN2);
  
  // Print the relay pin states
  Serial.println("\n=== ROBOT STATE ===");
  Serial.print("Relay Pins: [");
  Serial.print(r1p1); Serial.print(", ");
  Serial.print(r1p2); Serial.print(", ");
  Serial.print(r2p1); Serial.print(", ");
  Serial.print(r2p2); Serial.println("]");
  
  // Print motor states
  Serial.print("Motor 1: ");
  if (motor1_is_forward) Serial.println("FORWARD");
  else if (motor1_is_backward) Serial.println("BACKWARD");
  else Serial.println("STOPPED");
  
  Serial.print("Motor 2: ");
  if (motor2_is_forward) Serial.println("FORWARD");
  else if (motor2_is_backward) Serial.println("BACKWARD");
  else Serial.println("STOPPED");
  
  // Determine and print the overall robot direction
  Serial.print("Robot Direction: ");
  if (motor1_is_forward && motor2_is_forward) {
    Serial.println("FORWARD");
  } else if (motor1_is_backward && motor2_is_backward) {
    Serial.println("BACKWARD");
  } else if (motor1_is_backward && motor2_is_forward) {
    Serial.println("LEFT");
  } else if (motor1_is_forward && motor2_is_backward) {
    Serial.println("RIGHT");
  } else {
    Serial.println("STOPPED");
  }
  
  // Print current control mode
  Serial.print("Control Mode: ");
  switch (main_mode) {
    case CONTROL_BY_JOYSTICK:
      Serial.println("JOYSTICK");
      break;
    case CONTROL_BY_VOICE:
      Serial.println("VOICE");
      break;
    case CONTROL_BY_BLUETOOTH:
      Serial.println("BLUETOOTH");
      break;
    default:
      Serial.println("UNKNOWN");
      break;
  }
  Serial.println("==================\n");
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
    // Stop the robot before changing modes
    ROBOT_STOP();
    
    if(main_mode == CONTROL_BY_JOYSTICK){
      main_mode = CONTROL_BY_VOICE;
      Serial.println("Voice mode on");
      rec = STOP;
    }
    else if(main_mode == CONTROL_BY_VOICE) {
      main_mode = CONTROL_BY_BLUETOOTH;
      Serial.println("Bluetooth mode on");
      rec = STOP;
    }
    else {
      main_mode = CONTROL_BY_JOYSTICK;
      Serial.println("Joystick mode on");
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
  // #########   control based on mode  ############
  // ###############################################
  
  if(main_mode == CONTROL_BY_JOYSTICK){
    // Only process joystick if we can change direction (debounce)
    if (canChangeDirection()) {
      // 1. get joystick direction
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

  }
  else if(main_mode == CONTROL_BY_VOICE){
    // Only process voice commands if we can change direction (debounce)
    if (canChangeDirection()) {
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
          // No valid command recognized, maintain current state
          break;
      }
    }
  }
  else if(main_mode == CONTROL_BY_BLUETOOTH) {
    // Process any Bluetooth commands
    process_bluetooth_commands();
    // Serial.println("bluetooth mode on");
    
    // Continuously check for obstacles while moving
    // check_obstacles_while_moving();
  } 

  //dir = joystick_get_direction();
  //log_joystick_info();
  //log_voice_module_info();

  //delay(100);

  // Print current direction periodically
  unsigned long currentMillis = millis();
  if (currentMillis - lastDirectionPrintTime >= directionPrintInterval) {
    print_current_direction();
    lastDirectionPrintTime = currentMillis;
  }
}

void stop() {
  // led_forward.off();
  // led_backward.off();
  // led_left.off();

  // led_right.off();
  ROBOT_STOP();
}

void forward(int x_val, int y_val) {
  ROBOT_FORWARD();
  (void)x_val;
  (void)y_val;
}

void forward_left(int x_val, int y_val) {
  int x_distance_from_center = abs(x_val - 512);
  int y_distance_from_center = abs(y_val - 512);
  if (y_distance_from_center > x_distance_from_center) {
    ROBOT_FORWARD();
  } else {
    ROBOT_LEFT();
  }
}

void forward_right(int x_val, int y_val) {
  int x_distance_from_center = abs(x_val - 512);
  int y_distance_from_center = abs(y_val - 512);
  if (y_distance_from_center > x_distance_from_center) {
    ROBOT_FORWARD();
  } else {
    ROBOT_RIGHT();
  }
}

void backward(int x_val, int y_val) {
  ROBOT_BACKWARD();
  (void)x_val;
  (void)y_val;
}

void backward_left(int x_val, int y_val) {
  int x_distance_from_center = abs(x_val - 512);
  int y_distance_from_center = abs(y_val - 512);
  if (y_distance_from_center > x_distance_from_center) {
    ROBOT_BACKWARD();
  } else {
    ROBOT_LEFT();
  }
}

void backward_right(int x_val, int y_val) {
  int x_distance_from_center = abs(x_val - 512);
  int y_distance_from_center = abs(y_val - 512);
  if (y_distance_from_center > x_distance_from_center) {
    ROBOT_BACKWARD();
  } else {
    ROBOT_RIGHT();
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

