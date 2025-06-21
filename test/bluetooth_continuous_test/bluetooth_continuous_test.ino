/*
 * Bluetooth Continuous Movement Test
 * 
 * This sketch tests continuous movement control via Bluetooth
 * It's designed to diagnose and fix issues with stop-start movement
 */

// Relay pin definitions
#define RELAY1_PIN1     14  // Motor 1 control pin 1
#define RELAY1_PIN2     15  // Motor 1 control pin 2
#define RELAY2_PIN1     16  // Motor 2 control pin 1
#define RELAY2_PIN2     17  // Motor 2 control pin 2

// Track current motor states
bool motor1_is_forward = false;
bool motor1_is_backward = false;
bool motor2_is_forward = false;
bool motor2_is_backward = false;

// Track current direction
char currentDirection = 'S';

// Motor control functions
void motor_1_forward(){
  // Only change state if needed
  if (!motor1_is_forward) {
    // Turn off backward first if it's on
    if (motor1_is_backward) {
      digitalWrite(RELAY1_PIN2, LOW);
      motor1_is_backward = false;
      delay(20); // Small delay between relay operations
    }
    digitalWrite(RELAY1_PIN1, HIGH); 
    motor1_is_forward = true;
  }
}

void motor_1_backward(){
  // Only change state if needed
  if (!motor1_is_backward) {
    // Turn off forward first if it's on
    if (motor1_is_forward) {
      digitalWrite(RELAY1_PIN1, LOW);
      motor1_is_forward = false;
      delay(20); // Small delay between relay operations
    }
    digitalWrite(RELAY1_PIN2, HIGH);
    motor1_is_backward = true;
  }
}

void motor_1_off(){
  // Only change state if needed
  if (motor1_is_forward || motor1_is_backward) {
    digitalWrite(RELAY1_PIN1, LOW);
    digitalWrite(RELAY1_PIN2, LOW);
    motor1_is_forward = false;
    motor1_is_backward = false;
  }
}

void motor_2_forward(){
  // Only change state if needed
  if (!motor2_is_forward) {
    // Turn off backward first if it's on
    if (motor2_is_backward) {
      digitalWrite(RELAY2_PIN2, LOW);
      motor2_is_backward = false;
      delay(20); // Small delay between relay operations
    }
    digitalWrite(RELAY2_PIN1, HIGH);
    motor2_is_forward = true;
  }
}

void motor_2_backward(){
  // Only change state if needed
  if (!motor2_is_backward) {
    // Turn off forward first if it's on
    if (motor2_is_forward) {
      digitalWrite(RELAY2_PIN1, LOW);
      motor2_is_forward = false;
      delay(20); // Small delay between relay operations
    }
    digitalWrite(RELAY2_PIN2, HIGH);
    motor2_is_backward = true;
  }
}

void motor_2_off(){
  // Only change state if needed
  if (motor2_is_forward || motor2_is_backward) {
    digitalWrite(RELAY2_PIN1, LOW);
    digitalWrite(RELAY2_PIN2, LOW);
    motor2_is_forward = false;
    motor2_is_backward = false;
  }
}

// Robot movement functions
void robot_forward() {
  motor_1_forward();
  motor_2_forward();
}

void robot_backward() {
  motor_1_backward();
  motor_2_backward();
}

void robot_left() {
  motor_1_backward();
  motor_2_forward();
}

void robot_right() {
  motor_1_forward();
  motor_2_backward();
}

void robot_stop() {
  motor_1_off();
  motor_2_off();
}

void setup() {
  // Initialize serial communication
  Serial.begin(9600);
  Serial1.begin(9600); // Bluetooth on Serial1
  
  Serial.println("Bluetooth Continuous Movement Test");
  
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
  
  Serial.println("Ready to receive Bluetooth commands:");
  Serial.println("F: Forward, B: Backward, L: Left, R: Right, S: Stop");
}

void loop() {
  // Process Bluetooth commands
  if (Serial1.available()) {
    char command = Serial1.read();
    
    // Only process if it's a new command or a stop command
    if (command != currentDirection || command == 'S') {
      currentDirection = command;
      
      Serial.print("Command received: ");
      Serial.println(command);
      
      switch (command) {
        case 'F': // Forward
          robot_forward();
          Serial.println("Moving forward");
          break;
        case 'B': // Backward
          robot_backward();
          Serial.println("Moving backward");
          break;
        case 'L': // Left
          robot_left();
          Serial.println("Turning left");
          break;
        case 'R': // Right
          robot_right();
          Serial.println("Turning right");
          break;
        case 'S': // Stop
          robot_stop();
          Serial.println("Stopped");
          break;
      }
    }
  }
  
  // Print current motor states every 2 seconds for debugging
  static unsigned long lastPrintTime = 0;
  if (millis() - lastPrintTime > 2000) {
    lastPrintTime = millis();
    
    Serial.print("Current direction: ");
    switch (currentDirection) {
      case 'F': Serial.println("Forward"); break;
      case 'B': Serial.println("Backward"); break;
      case 'L': Serial.println("Left"); break;
      case 'R': Serial.println("Right"); break;
      case 'S': Serial.println("Stopped"); break;
      default: Serial.println("Unknown"); break;
    }
    
    Serial.print("Motor 1: ");
    if (motor1_is_forward) Serial.println("Forward");
    else if (motor1_is_backward) Serial.println("Backward");
    else Serial.println("Off");
    
    Serial.print("Motor 2: ");
    if (motor2_is_forward) Serial.println("Forward");
    else if (motor2_is_backward) Serial.println("Backward");
    else Serial.println("Off");
    
    Serial.println("-------------------");
  }
} 