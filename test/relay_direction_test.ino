/*
 * Relay Direction Diagnostic Test
 * 
 * This sketch tests each relay and direction individually
 * to diagnose issues with specific movement directions.
 */
#include <Arduino.h>
// Relay pin definitions
#define RELAY1_PIN1     14  // Motor 1 control pin 1
#define RELAY1_PIN2     15  // Motor 1 control pin 2
#define RELAY2_PIN1     16  // Motor 2 control pin 1
#define RELAY2_PIN2     17  // Motor 2 control pin 2

void setup() {
  // Initialize serial communication
  Serial.begin(9600);
  while (!Serial) {
    ; // Wait for serial port to connect
  }
  
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
  
  Serial.println("\n\n=== Relay Direction Diagnostic Test ===");
  Serial.println("This tool will help diagnose issues with specific movement directions");
  Serial.println("Testing each relay individually...");
  delay(2000);
}

void loop() {
  // Test each relay individually
  
  // All relays off
  allRelaysOff();
  Serial.println("\n1. All relays OFF - motors should be stopped");
  waitForInput();
  
  // Test RELAY1_PIN1 (Motor 1 Forward)
  allRelaysOff();
  digitalWrite(RELAY1_PIN1, HIGH);
  Serial.println("\n2. Testing RELAY1_PIN1 (Motor 1 Forward pin)");
  Serial.println("   Only Motor 1 should be moving forward");
  waitForInput();
  
  // Test RELAY1_PIN2 (Motor 1 Backward)
  allRelaysOff();
  digitalWrite(RELAY1_PIN2, HIGH);
  Serial.println("\n3. Testing RELAY1_PIN2 (Motor 1 Backward pin)");
  Serial.println("   Only Motor 1 should be moving backward");
  waitForInput();
  
  // Test RELAY2_PIN1 (Motor 2 Forward)
  allRelaysOff();
  digitalWrite(RELAY2_PIN1, HIGH);
  Serial.println("\n4. Testing RELAY2_PIN1 (Motor 2 Forward pin)");
  Serial.println("   Only Motor 2 should be moving forward");
  waitForInput();
  
  // Test RELAY2_PIN2 (Motor 2 Backward)
  allRelaysOff();
  digitalWrite(RELAY2_PIN2, HIGH);
  Serial.println("\n5. Testing RELAY2_PIN2 (Motor 2 Backward pin)");
  Serial.println("   Only Motor 2 should be moving backward");
  waitForInput();
  
  // Test robot movement directions
  
  // Forward
  allRelaysOff();
  digitalWrite(RELAY1_PIN1, HIGH);
  digitalWrite(RELAY2_PIN1, HIGH);
  Serial.println("\n6. Testing FORWARD movement");
  Serial.println("   Both motors should be moving forward");
  waitForInput();
  
  // Backward
  allRelaysOff();
  digitalWrite(RELAY1_PIN2, HIGH);
  digitalWrite(RELAY2_PIN2, HIGH);
  Serial.println("\n7. Testing BACKWARD movement");
  Serial.println("   Both motors should be moving backward");
  waitForInput();
  
  // Left
  allRelaysOff();
  digitalWrite(RELAY1_PIN2, HIGH);
  digitalWrite(RELAY2_PIN1, HIGH);
  Serial.println("\n8. Testing LEFT movement");
  Serial.println("   Motor 1 should be moving backward");
  Serial.println("   Motor 2 should be moving forward");
  waitForInput();
  
  // Right
  allRelaysOff();
  digitalWrite(RELAY1_PIN1, HIGH);
  digitalWrite(RELAY2_PIN2, HIGH);
  Serial.println("\n9. Testing RIGHT movement");
  Serial.println("   Motor 1 should be moving forward");
  Serial.println("   Motor 2 should be moving backward");
  waitForInput();
  
  // Test complete
  allRelaysOff();
  Serial.println("\nTest cycle complete. Press any key to restart...");
  waitForInput();
}

// Turn off all relays
void allRelaysOff() {
  digitalWrite(RELAY1_PIN1, LOW);
  digitalWrite(RELAY1_PIN2, LOW);
  digitalWrite(RELAY2_PIN1, LOW);
  digitalWrite(RELAY2_PIN2, LOW);
  delay(500); // Give time for relays to settle
}

// Wait for user input
void waitForInput() {
  Serial.println("Press any key to continue...");
  while (Serial.available()) {
    Serial.read(); // Clear input buffer
  }
  while (!Serial.available()) {
    delay(100); // Wait for input
  }
  while (Serial.available()) {
    Serial.read(); // Clear input buffer
  }
} 