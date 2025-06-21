/*
 * Relay Module Calibration Sketch
 * 
 * This sketch helps determine the correct logic levels for your specific 2-channel relay module.
 * Some relay modules are active-LOW (relay activates when pin is LOW)
 * Others are active-HIGH (relay activates when pin is HIGH)
 * 
 * Instructions:
 * 1. Upload this sketch to your Arduino
 * 2. Open the Serial Monitor at 9600 baud
 * 3. Follow the prompts to test different relay states
 * 4. Determine if your relay is active-LOW or active-HIGH
 * 5. Update your main code accordingly
 */

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
  
  // Initialize all relay pins to LOW
  digitalWrite(RELAY1_PIN1, LOW);
  digitalWrite(RELAY1_PIN2, LOW);
  digitalWrite(RELAY2_PIN1, LOW);
  digitalWrite(RELAY2_PIN2, LOW);
  
  Serial.println("\n\n=== Relay Module Calibration Tool ===");
  Serial.println("This tool will help determine if your relay module is active-HIGH or active-LOW");
  Serial.println("Follow the prompts and observe the relay behavior");
  Serial.println("\nAll relays should be OFF now. If any relay is ON, your module might be active-LOW.");
  Serial.println("\nPress any key to continue...");
  waitForInput();
}

void loop() {
  // Test 1: Test active-HIGH hypothesis
  Serial.println("\n=== Test 1: Testing active-HIGH hypothesis ===");
  Serial.println("Setting all pins HIGH. If relays turn ON, they are active-HIGH.");
  Serial.println("If relays remain OFF, they are likely active-LOW.");
  
  digitalWrite(RELAY1_PIN1, HIGH);
  digitalWrite(RELAY1_PIN2, HIGH);
  digitalWrite(RELAY2_PIN1, HIGH);
  digitalWrite(RELAY2_PIN2, HIGH);
  
  Serial.println("\nDid the relays turn ON? (y/n)");
  if (readYesNo()) {
    Serial.println("Your relays are active-HIGH.");
  } else {
    Serial.println("Your relays are likely active-LOW.");
  }
  
  // Reset relays
  digitalWrite(RELAY1_PIN1, LOW);
  digitalWrite(RELAY1_PIN2, LOW);
  digitalWrite(RELAY2_PIN1, LOW);
  digitalWrite(RELAY2_PIN2, LOW);
  delay(1000);
  
  // Test 2: Motor direction test
  Serial.println("\n=== Test 2: Motor Direction Test ===");
  Serial.println("We'll test each motor direction to verify correct wiring.");
  
  // Test Motor 1 Forward
  Serial.println("\nTesting Motor 1 Forward:");
  Serial.println("Setting RELAY1_PIN1=HIGH, RELAY1_PIN2=LOW");
  digitalWrite(RELAY1_PIN1, HIGH);
  digitalWrite(RELAY1_PIN2, LOW);
  Serial.println("Is Motor 1 moving forward? (y/n)");
  boolean motor1ForwardCorrect = readYesNo();
  
  // Reset
  digitalWrite(RELAY1_PIN1, LOW);
  digitalWrite(RELAY1_PIN2, LOW);
  delay(1000);
  
  // Test Motor 1 Backward
  Serial.println("\nTesting Motor 1 Backward:");
  Serial.println("Setting RELAY1_PIN1=LOW, RELAY1_PIN2=HIGH");
  digitalWrite(RELAY1_PIN1, LOW);
  digitalWrite(RELAY1_PIN2, HIGH);
  Serial.println("Is Motor 1 moving backward? (y/n)");
  boolean motor1BackwardCorrect = readYesNo();
  
  // Reset
  digitalWrite(RELAY1_PIN1, LOW);
  digitalWrite(RELAY1_PIN2, LOW);
  delay(1000);
  
  // Test Motor 2 Forward
  Serial.println("\nTesting Motor 2 Forward:");
  Serial.println("Setting RELAY2_PIN1=HIGH, RELAY2_PIN2=LOW");
  digitalWrite(RELAY2_PIN1, HIGH);
  digitalWrite(RELAY2_PIN2, LOW);
  Serial.println("Is Motor 2 moving forward? (y/n)");
  boolean motor2ForwardCorrect = readYesNo();
  
  // Reset
  digitalWrite(RELAY2_PIN1, LOW);
  digitalWrite(RELAY2_PIN2, LOW);
  delay(1000);
  
  // Test Motor 2 Backward
  Serial.println("\nTesting Motor 2 Backward:");
  Serial.println("Setting RELAY2_PIN1=LOW, RELAY2_PIN2=HIGH");
  digitalWrite(RELAY2_PIN1, LOW);
  digitalWrite(RELAY2_PIN2, HIGH);
  Serial.println("Is Motor 2 moving backward? (y/n)");
  boolean motor2BackwardCorrect = readYesNo();
  
  // Reset
  digitalWrite(RELAY2_PIN1, LOW);
  digitalWrite(RELAY2_PIN2, LOW);
  delay(1000);
  
  // Results
  Serial.println("\n=== Calibration Results ===");
  if (motor1ForwardCorrect && motor1BackwardCorrect && motor2ForwardCorrect && motor2BackwardCorrect) {
    Serial.println("All motor directions are correct!");
    Serial.println("Your current pin configuration is working correctly.");
  } else {
    Serial.println("Some motor directions need adjustment:");
    
    if (!motor1ForwardCorrect) {
      Serial.println("- Motor 1 Forward direction is incorrect");
      Serial.println("  Try swapping RELAY1_PIN1 and RELAY1_PIN2 in your code");
    }
    
    if (!motor1BackwardCorrect) {
      Serial.println("- Motor 1 Backward direction is incorrect");
      Serial.println("  Try swapping RELAY1_PIN1 and RELAY1_PIN2 in your code");
    }
    
    if (!motor2ForwardCorrect) {
      Serial.println("- Motor 2 Forward direction is incorrect");
      Serial.println("  Try swapping RELAY2_PIN1 and RELAY2_PIN2 in your code");
    }
    
    if (!motor2BackwardCorrect) {
      Serial.println("- Motor 2 Backward direction is incorrect");
      Serial.println("  Try swapping RELAY2_PIN1 and RELAY2_PIN2 in your code");
    }
  }
  
  // Final test: Robot movement
  Serial.println("\n=== Final Test: Robot Movement ===");
  Serial.println("Let's test the complete robot movements.");
  
  // Forward
  Serial.println("\nTesting FORWARD movement (both motors forward)");
  digitalWrite(RELAY1_PIN1, HIGH);
  digitalWrite(RELAY1_PIN2, LOW);
  digitalWrite(RELAY2_PIN1, HIGH);
  digitalWrite(RELAY2_PIN2, LOW);
  Serial.println("Is the robot moving forward? (y/n)");
  boolean forwardCorrect = readYesNo();
  
  // Reset
  digitalWrite(RELAY1_PIN1, LOW);
  digitalWrite(RELAY1_PIN2, LOW);
  digitalWrite(RELAY2_PIN1, LOW);
  digitalWrite(RELAY2_PIN2, LOW);
  delay(1000);
  
  // Backward
  Serial.println("\nTesting BACKWARD movement (both motors backward)");
  digitalWrite(RELAY1_PIN1, LOW);
  digitalWrite(RELAY1_PIN2, HIGH);
  digitalWrite(RELAY2_PIN1, LOW);
  digitalWrite(RELAY2_PIN2, HIGH);
  Serial.println("Is the robot moving backward? (y/n)");
  boolean backwardCorrect = readYesNo();
  
  // Reset
  digitalWrite(RELAY1_PIN1, LOW);
  digitalWrite(RELAY1_PIN2, LOW);
  digitalWrite(RELAY2_PIN1, LOW);
  digitalWrite(RELAY2_PIN2, LOW);
  delay(1000);
  
  // Left
  Serial.println("\nTesting LEFT turn (Motor 1 backward, Motor 2 forward)");
  digitalWrite(RELAY1_PIN1, LOW);
  digitalWrite(RELAY1_PIN2, HIGH);
  digitalWrite(RELAY2_PIN1, HIGH);
  digitalWrite(RELAY2_PIN2, LOW);
  Serial.println("Is the robot turning left? (y/n)");
  boolean leftCorrect = readYesNo();
  
  // Reset
  digitalWrite(RELAY1_PIN1, LOW);
  digitalWrite(RELAY1_PIN2, LOW);
  digitalWrite(RELAY2_PIN1, LOW);
  digitalWrite(RELAY2_PIN2, LOW);
  delay(1000);
  
  // Right
  Serial.println("\nTesting RIGHT turn (Motor 1 forward, Motor 2 backward)");
  digitalWrite(RELAY1_PIN1, HIGH);
  digitalWrite(RELAY1_PIN2, LOW);
  digitalWrite(RELAY2_PIN1, LOW);
  digitalWrite(RELAY2_PIN2, HIGH);
  Serial.println("Is the robot turning right? (y/n)");
  boolean rightCorrect = readYesNo();
  
  // Reset
  digitalWrite(RELAY1_PIN1, LOW);
  digitalWrite(RELAY1_PIN2, LOW);
  digitalWrite(RELAY2_PIN1, LOW);
  digitalWrite(RELAY2_PIN2, LOW);
  
  // Final results
  Serial.println("\n=== Final Results ===");
  if (forwardCorrect && backwardCorrect && leftCorrect && rightCorrect) {
    Serial.println("All robot movements are working correctly!");
    Serial.println("Your relay module and motor connections are configured correctly.");
  } else {
    Serial.println("Some robot movements need adjustment:");
    
    if (!forwardCorrect) {
      Serial.println("- Forward movement is incorrect");
    }
    
    if (!backwardCorrect) {
      Serial.println("- Backward movement is incorrect");
    }
    
    if (!leftCorrect) {
      Serial.println("- Left turn is incorrect");
    }
    
    if (!rightCorrect) {
      Serial.println("- Right turn is incorrect");
    }
    
    Serial.println("\nYou may need to adjust the motor_1_forward(), motor_1_backward(),");
    Serial.println("motor_2_forward(), and motor_2_backward() functions in your code.");
  }
  
  Serial.println("\nCalibration complete. Press any key to restart the test...");
  waitForInput();
}

// Helper function to wait for user input
void waitForInput() {
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

// Helper function to read yes/no response
boolean readYesNo() {
  while (Serial.available()) {
    Serial.read(); // Clear input buffer
  }
  
  while (true) {
    if (Serial.available()) {
      char c = Serial.read();
      if (c == 'y' || c == 'Y') {
        return true;
      } else if (c == 'n' || c == 'N') {
        return false;
      }
    }
    delay(100);
  }
} 