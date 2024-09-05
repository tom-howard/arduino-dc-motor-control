int potValue = 0;
// Pin assignments for Motor Driver Inputs:
const int pinAI1 = 8; const int pinAI2 = 7; 
const int pinPWM = 5; const int pinStandby = 9; 
// Some variables for controlling code execution rates:
unsigned long timestamp = millis();
unsigned long elapsed = 0;
// Arduino output variables:
boolean AI1 = false; boolean AI2 = true;  
int pwmValue = 100; // PWM value to be written to PWMA

void setup(){
  // Configure the Arduino digital output pins
  pinMode(pinAI1, OUTPUT); pinMode(pinAI2, OUTPUT); 
  pinMode(pinPWM, OUTPUT); pinMode(pinStandby, OUTPUT);
  //Initialize the serial port
  Serial.begin(9600);
  // Set standby to high to enable motor operation:
  digitalWrite(pinStandby, HIGH);
}

void loop(){
  // read the value of the potentiometer
  potValue = analogRead(A0);
  // Scale this to an applicable PWM range for the motor:
  potValue = map(potValue, 0, 1023, -200, 200);
  // change the motor direction based on the sign of potValue:
  if (potValue < 0){
    AI1 = true; AI2 = false;
  }
  else {
    AI1 = false; AI2 = true;
  }
  pwmValue = abs(potValue);
  
  // Send signals to Pins AI1 and AI2 (direction of rotation)
  digitalWrite(pinAI1, AI1); digitalWrite(pinAI2, AI2);
  // Write the pwmValue to the PWM pin (to control motor speed)
  analogWrite(pinPWM, pwmValue);
  
  elapsed = millis() - timestamp;    
  if (elapsed > 250){
    // Print to the serial monitor:
    Serial.print("PWM value (signed) = "); Serial.print(potValue);
    Serial.print(" (A1|A2 = "); Serial.print(AI1);
    Serial.print("|"); Serial.print(AI2); Serial.println(").");
    timestamp = millis(); // reset the timestamp
  }
}
