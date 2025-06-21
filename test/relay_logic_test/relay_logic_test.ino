/*
 * Relay Logic Test
 * 
 * This sketch tests whether the relay module is active-LOW or active-HIGH
 * and provides alternative motor control functions for each case.
 */

// Relay pin definitions
#define RELAY1_PIN1     14  // Motor 1 control pin 1
#define RELAY1_PIN2     15  // Motor 1 control pin 2
#define RELAY2_PIN1     16  // Motor 2 control pin 1
#define RELAY2_PIN2     17  // Motor 2 control pin 2

// Test mode
enum TestMode {
  ACTIVE_HIGH,
  ACTIVE_LOW
};

TestMode currentMode = ACTIVE_HIGH; // Start with active-HIGH test

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
  
  // Initialize all relay pins to LOW
  allPinsLow();
  
  Serial.println("\n\n=== Relay Logic Test ===");
  Serial.println("This tool will help determine if your relay module is active-LOW or active-HIGH");
  Serial.println("and test motor control functions for each case.");
  delay(2000);
}

void loop() {
  if (currentMode == ACTIVE_HIGH) {
    testActiveHighMode();
    
    Serial.println("\nSwitching to ACTIVE-LOW test mode...");
    currentMode = ACTIVE_LOW;
    delay(2000);
  } else {
    testActiveLowMode();
    
    Serial.println("\nTest complete. Press any key to restart...");
    waitForInput();
    
    currentMode = ACTIVE_HIGH;
  }
}

void testActiveHighMode() {
  Serial.println("\n=== Testing ACTIVE-HIGH Mode ===");
  Serial.println("In this mode, HIGH activates the relay, LOW deactivates it");
  
  // All relays off
  allPinsLow();
  Serial.println("\n1. All relays should be OFF now (all pins LOW)");
  waitForInput();
  
  // Test forward movement (active-HIGH)
  allPinsLow();
  Serial.println("\n2. Testing FORWARD movement (active-HIGH)");
  Serial.println("   Setting RELAY1_PIN1=HIGH, RELAY1_PIN2=LOW, RELAY2_PIN1=HIGH, RELAY2_PIN2=LOW");
  digitalWrite(RELAY1_PIN1, HIGH);
  digitalWrite(RELAY1_PIN2, LOW);
  digitalWrite(RELAY2_PIN1, HIGH);
  digitalWrite(RELAY2_PIN2, LOW);
  Serial.println("   Robot should be moving FORWARD");
  waitForInput();
  
  // Test backward movement (active-HIGH)
  allPinsLow();
  Serial.println("\n3. Testing BACKWARD movement (active-HIGH)");
  Serial.println("   Setting RELAY1_PIN1=LOW, RELAY1_PIN2=HIGH, RELAY2_PIN1=LOW, RELAY2_PIN2=HIGH");
  digitalWrite(RELAY1_PIN1, LOW);
  digitalWrite(RELAY1_PIN2, HIGH);
  digitalWrite(RELAY2_PIN1, LOW);
  digitalWrite(RELAY2_PIN2, HIGH);
  Serial.println("   Robot should be moving BACKWARD");
  waitForInput();
  
  // Test left movement (active-HIGH)
  allPinsLow();
  Serial.println("\n4. Testing LEFT movement (active-HIGH)");
  Serial.println("   Setting RELAY1_PIN1=LOW, RELAY1_PIN2=HIGH, RELAY2_PIN1=HIGH, RELAY2_PIN2=LOW");
  digitalWrite(RELAY1_PIN1, LOW);
  digitalWrite(RELAY1_PIN2, HIGH);
  digitalWrite(RELAY2_PIN1, HIGH);
  digitalWrite(RELAY2_PIN2, LOW);
  Serial.println("   Robot should be turning LEFT");
  waitForInput();
  
  // Test right movement (active-HIGH)
  allPinsLow();
  Serial.println("\n5. Testing RIGHT movement (active-HIGH)");
  Serial.println("   Setting RELAY1_PIN1=HIGH, RELAY1_PIN2=LOW, RELAY2_PIN1=LOW, RELAY2_PIN2=HIGH");
  digitalWrite(RELAY1_PIN1, HIGH);
  digitalWrite(RELAY1_PIN2, LOW);
  digitalWrite(RELAY2_PIN1, LOW);
  digitalWrite(RELAY2_PIN2, HIGH);
  Serial.println("   Robot should be turning RIGHT");
  waitForInput();
  
  // All relays off
  allPinsLow();
}

void testActiveLowMode() {
  Serial.println("\n=== Testing ACTIVE-LOW Mode ===");
  Serial.println("In this mode, LOW activates the relay, HIGH deactivates it");
  
  // All relays off
  allPinsHigh();
  Serial.println("\n1. All relays should be OFF now (all pins HIGH)");
  waitForInput();
  
  // Test forward movement (active-LOW)
  allPinsHigh();
  Serial.println("\n2. Testing FORWARD movement (active-LOW)");
  Serial.println("   Setting RELAY1_PIN1=LOW, RELAY1_PIN2=HIGH, RELAY2_PIN1=LOW, RELAY2_PIN2=HIGH");
  digitalWrite(RELAY1_PIN1, LOW);
  digitalWrite(RELAY1_PIN2, HIGH);
  digitalWrite(RELAY2_PIN1, LOW);
  digitalWrite(RELAY2_PIN2, HIGH);
  Serial.println("   Robot should be moving FORWARD");
  waitForInput();
  
  // Test backward movement (active-LOW)
  allPinsHigh();
  Serial.println("\n3. Testing BACKWARD movement (active-LOW)");
  Serial.println("   Setting RELAY1_PIN1=HIGH, RELAY1_PIN2=LOW, RELAY2_PIN1=HIGH, RELAY2_PIN2=LOW");
  digitalWrite(RELAY1_PIN1, HIGH);
  digitalWrite(RELAY1_PIN2, LOW);
  digitalWrite(RELAY2_PIN1, HIGH);
  digitalWrite(RELAY2_PIN2, LOW);
  Serial.println("   Robot should be moving BACKWARD");
  waitForInput();
  
  // Test left movement (active-LOW)
  allPinsHigh();
  Serial.println("\n4. Testing LEFT movement (active-LOW)");
  Serial.println("   Setting RELAY1_PIN1=HIGH, RELAY1_PIN2=LOW, RELAY2_PIN1=LOW, RELAY2_PIN2=HIGH");
  digitalWrite(RELAY1_PIN1, HIGH);
  digitalWrite(RELAY1_PIN2, LOW);
  digitalWrite(RELAY2_PIN1, LOW);
  digitalWrite(RELAY2_PIN2, HIGH);
  Serial.println("   Robot should be turning LEFT");
  waitForInput();
  
  // Test right movement (active-LOW)
  allPinsHigh();
  Serial.println("\n5. Testing RIGHT movement (active-LOW)");
  Serial.println("   Setting RELAY1_PIN1=LOW, RELAY1_PIN2=HIGH, RELAY2_PIN1=HIGH, RELAY2_PIN2=LOW");
  digitalWrite(RELAY1_PIN1, LOW);
  digitalWrite(RELAY1_PIN2, HIGH);
  digitalWrite(RELAY2_PIN1, HIGH);
  digitalWrite(RELAY2_PIN2, LOW);
  Serial.println("   Robot should be turning RIGHT");
  waitForInput();
  
  // All relays off
  allPinsHigh();
}

// Set all pins to LOW
void allPinsLow() {
  digitalWrite(RELAY1_PIN1, LOW);
  digitalWrite(RELAY1_PIN2, LOW);
  digitalWrite(RELAY2_PIN1, LOW);
  digitalWrite(RELAY2_PIN2, LOW);
  delay(500); // Give time for relays to settle
}

// Set all pins to HIGH
void allPinsHigh() {
  digitalWrite(RELAY1_PIN1, HIGH);
  digitalWrite(RELAY1_PIN2, HIGH);
  digitalWrite(RELAY2_PIN1, HIGH);
  digitalWrite(RELAY2_PIN2, HIGH);
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