/*
 * Relay Module Test Sketch
 * 
 * This sketch tests the 2-channel relay module connected to an Arduino Mega 2560.
 * It cycles through different movement patterns to verify proper relay operation.
 * 
 * Connections:
 * - Relay 1 Channel 1: Pin 14
 * - Relay 1 Channel 2: Pin 15
 * - Relay 2 Channel 1: Pin 16
 * - Relay 2 Channel 2: Pin 17
 */

// Relay pin definitions
#define RELAY1_PIN1     14  // Motor 1 control pin 1
#define RELAY1_PIN2     15  // Motor 1 control pin 2
#define RELAY2_PIN1     16  // Motor 2 control pin 1
#define RELAY2_PIN2     17  // Motor 2 control pin 2

// Motor control functions
void motor_1_forward() {
  digitalWrite(RELAY1_PIN1, HIGH); 
  digitalWrite(RELAY1_PIN2, LOW);
}

void motor_1_backward() {
  digitalWrite(RELAY1_PIN1, LOW); 
  digitalWrite(RELAY1_PIN2, HIGH);
}

void motor_1_off() {
  digitalWrite(RELAY1_PIN1, LOW);
  digitalWrite(RELAY1_PIN2, LOW);
}

void motor_2_forward() {
  digitalWrite(RELAY2_PIN1, HIGH);
  digitalWrite(RELAY2_PIN2, LOW);
}

void motor_2_backward() {
  digitalWrite(RELAY2_PIN1, LOW);
  digitalWrite(RELAY2_PIN2, HIGH);
}

void motor_2_off() {
  digitalWrite(RELAY2_PIN1, LOW);
  digitalWrite(RELAY2_PIN2, LOW);
}

// Robot movement functions
void robot_forward() {
  motor_1_forward();
  motor_2_forward();
  Serial.println("Moving forward");
}

void robot_backward() {
  motor_1_backward();
  motor_2_backward();
  Serial.println("Moving backward");
}

void robot_left() {
  motor_1_backward();
  motor_2_forward();
  Serial.println("Turning left");
}

void robot_right() {
  motor_1_forward();
  motor_2_backward();
  Serial.println("Turning right");
}

void robot_stop() {
  motor_1_off();
  motor_2_off();
  Serial.println("Stopped");
}

void setup() {
  // Initialize serial communication
  Serial.begin(9600);
  Serial.println("Relay Module Test");
  
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
  
  Serial.println("Testing relay module in 3 seconds...");
  delay(3000);
}

void loop() {
  // Test sequence
  
  // 1. Stop (ensure we start from a known state)
  robot_stop();
  delay(2000);
  
  // 2. Forward
  robot_forward();
  delay(3000);
  
  // 3. Stop
  robot_stop();
  delay(2000);
  
  // 4. Backward
  robot_backward();
  delay(3000);
  
  // 5. Stop
  robot_stop();
  delay(2000);
  
  // 6. Left
  robot_left();
  delay(3000);
  
  // 7. Stop
  robot_stop();
  delay(2000);
  
  // 8. Right
  robot_right();
  delay(3000);
  
  // 9. Stop
  robot_stop();
  delay(2000);
  
  Serial.println("Test cycle complete. Restarting in 5 seconds...");
  delay(5000);
} 