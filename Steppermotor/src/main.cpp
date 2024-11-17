#include <AccelStepper.h>

// Define pins for ULN2003 driver
#define IN1 D5  
#define IN2 D6  
#define IN3 D7  
#define IN4 D8  

// Define the AccelStepper interface type; 4 wire motor in half step mode:
#define MotorInterfaceType 8

// Initialize with sequence IN1-IN3-IN2-IN4 for proper stepping
AccelStepper stepper = AccelStepper(MotorInterfaceType, IN1, IN3, IN2, IN4);

void setup() {
  Serial.begin(115200);
  
  // Set the maximum steps per second and acceleration
  stepper.setMaxSpeed(1000.0);
  stepper.setAcceleration(200.0);
  stepper.setSpeed(500);  // Set constant speed
  
  Serial.println("Stepper motor program started");
}

void loop() {
  // Move continuously at constant speed
  stepper.runSpeed();
}