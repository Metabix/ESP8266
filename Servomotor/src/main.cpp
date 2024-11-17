#include <Servo.h>

// Create servo object
Servo myServo;

// Pin definition
const int servoPin = D3;  // GPIO0

void setup() {
  // Start serial communication for debugging
  Serial.begin(115200);
  
  // Attach servo to pin
  myServo.attach(servoPin);
  
  Serial.println("Servo motor initialized");
}

void loop() {
  // Rotate continuously clockwise
  myServo.write(180);  // Full speed clockwise
  delay(2000);         // Run for 2 seconds
  
  // Rotate continuously counter-clockwise
  myServo.write(0);    // Full speed counter-clockwise
  delay(2000);         // Run for 2 seconds
  
  // Optional: Stop briefly
  // myServo.write(90); // Stop
  // delay(1000);       // Wait for 1 second
}