#include "main.h"

// Control mode for Bluetooth
typedef enum {
  BT_REMOTE_CONTROL,
  BT_VOICE_CONTROL
} bluetooth_mode_t;

// Current Bluetooth control mode
bluetooth_mode_t bt_mode = BT_REMOTE_CONTROL;

// Flag to track if robot is currently moving
bool isMoving = false;

extern Ultrasonic front_utrasonic, back_utrasonic;

// Use Serial1 for Bluetooth
#define bluetoothSerial Serial1

/**
 * Initialize Bluetooth communication
 */
void bluetooth_init() {
  bluetoothSerial.begin(9600); // Most modules use 9600 baud
  Serial.println("Bluetooth module initialized");
}

/**
 * Process incoming Bluetooth commands
 * Returns true if a command was processed, false otherwise
 */
bool process_bluetooth_commands() {
  if (bluetoothSerial.available()) {
    char value = bluetoothSerial.read();
    Serial.print("Received command: ");
    Serial.println(value);
    
    // Determine mode based on the received command
    // Remote commands: 'F', 'B', 'L', 'R', 'S'
    // Voice commands: '^', '-', '<', '>', '*'
    if (value == '^' || value == '-' || value == '<' || value == '>' || value == '*') {
      bt_mode = BT_VOICE_CONTROL;
      process_voice_command(value);
    } else {
      bt_mode = BT_REMOTE_CONTROL;
      process_remote_command(value);
    }
    
    return true; // Command was processed
  }
  
  return false; // No command available
}

/**
 * Process remote control commands received via Bluetooth
 */
void process_remote_command(char command) {
  switch (command) {
    case 'F': // Forward
      // Check if path is clear before moving forward
      if (front_dist > MINIMUM_ACCEPTED_DISTANCE) {
        ROBOT_FORWARD();
        isMoving = true;
        Serial.println("Moving forward via Bluetooth");
      } else {
        ROBOT_STOP();
        Serial.println("Obstacle ahead, cannot move forward");
      }
      break;
      
    case 'B': // Backward
      // Check if path is clear before moving backward
      if (back_dist > MINIMUM_ACCEPTED_DISTANCE) {
        ROBOT_BACKWARD();
        isMoving = true;
        Serial.println("Moving backward via Bluetooth");
      } else {
        ROBOT_STOP();
        Serial.println("Obstacle behind, cannot move backward");
      }
      break;
      
    case 'L': // Left
      ROBOT_LEFT();
      delay(500); // Turn for a short time
      ROBOT_STOP();
      Serial.println("Turned left via Bluetooth");
      break;
      
    case 'R': // Right
      ROBOT_RIGHT();
      delay(500); // Turn for a short time
      ROBOT_STOP();
      Serial.println("Turned right via Bluetooth");
      break;
      
    case 'S': // Stop
      ROBOT_STOP();
      isMoving = false;
      Serial.println("Stopped via Bluetooth");
      break;
      
    default:
      // Unknown command, do nothing
      break;
  }
}

/**
 * Process voice control commands received via Bluetooth
 */
void process_voice_command(char command) {
  switch (command) {
    case '^': // Forward
      // Check if path is clear before moving forward
      ROBOT_FORWARD();
      isMoving = true;
      // Serial.println("Moving forward via voice command");
      // if (front_dist > MINIMUM_ACCEPTED_DISTANCE) {
      //   ROBOT_FORWARD();
      //   isMoving = true;
      //   Serial.println("Moving forward via voice command");
      // } else {
      //   ROBOT_STOP();
      //   Serial.println("Obstacle ahead, cannot move forward");
      // }
      break;
      
    case '-': // Backward
      // Check if path is clear before moving backward
      ROBOT_BACKWARD();
      isMoving = true;
      Serial.println("Moving backward via voice command");
      // if (back_dist > MINIMUM_ACCEPTED_DISTANCE) {
      //   ROBOT_BACKWARD();
      //   isMoving = true;
      //   Serial.println("Moving backward via voice command");
      // } else {
      //   ROBOT_STOP();
      //   Serial.println("Obstacle behind, cannot move backward");
      // }
      break;
      
    case '<': // Left
      ROBOT_LEFT();
      // delay(2500); // Turn for a short time
      // ROBOT_STOP();
      Serial.println("Turned left via voice command");
      break;
      
    case '>': // Right
      ROBOT_RIGHT();
      // delay(2500); // Turn for a short time
      // ROBOT_STOP();
      Serial.println("Turned right via voice command");
      break;
      
    case '*': // Stop
      ROBOT_STOP();
      isMoving = false;
      Serial.println("Stopped via voice command");
      break;
      
    default:
      // Unknown command, do nothing
      break;
  }
}

/**
 * Check for obstacles while moving and stop if necessary
 * Call this function repeatedly in the main loop when robot is moving
 */
void check_obstacles_while_moving() {
  if (isMoving) {
    // Update distance readings
    front_dist = front_utrasonic.get_distance();
    Serial.print("Front distance: "); 
    Serial.println(front_dist);
    back_dist = back_utrasonic.get_distance();
    Serial.print("Back distance: ");
    Serial.println(back_dist);
    // Check for obstacles based on current direction
    if (motor_is_moving_forward() && front_dist <= MINIMUM_ACCEPTED_DISTANCE) {
      ROBOT_STOP();
      isMoving = false;
      Serial.println("Obstacle detected ahead! Stopping.");
    } else if (motor_is_moving_backward() && back_dist <= MINIMUM_ACCEPTED_DISTANCE) {
      ROBOT_STOP();
      isMoving = false;
      Serial.println("Obstacle detected behind! Stopping.");
    }
  }
}

/**
 * Check if motors are currently moving forward
 */
bool motor_is_moving_forward() {
  // This is a simplified check - adjust based on your motor control implementation
  // Assumes motors are moving forward if pin 14 and 16 are HIGH
  return (digitalRead(14) == HIGH && digitalRead(16) == HIGH);
}

/**
 * Check if motors are currently moving backward
 */
bool motor_is_moving_backward() {
  // This is a simplified check - adjust based on your motor control implementation
  // Assumes motors are moving backward if pin 15 and 17 are HIGH
  return (digitalRead(15) == HIGH && digitalRead(17) == HIGH);
} 