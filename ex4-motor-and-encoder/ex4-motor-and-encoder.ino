int potValue = 0;
float motorSpeed = 0;

const byte encoderAPin = 2;
volatile long counterA = 0;
unsigned long counterAlast = 0;
unsigned long counterAdiff = 0;
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
  attachInterrupt(
    digitalPinToInterrupt(encoderAPin),
    encoderAInterrupt,
    FALLING
  );

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
    counterAdiff = counterA-counterAlast;
    counterAlast = counterA;
    // calculate motor speed:
    motorSpeed = float(60*counterAdiff*1000)/float(8*120*elapsed);
      
    // Print to the serial monitor:
    Serial.print("Speed = "); Serial.print(motorSpeed); Serial.print("rpm: ");
    Serial.print(counterAdiff); Serial.print(" encoder pulses in ");
    Serial.print(elapsed); Serial.print(" ms (PWM value = ");
    Serial.print(pwmValue); Serial.println(").");
    timestamp = millis(); // reset the timestamp
  }
}

// Interrupt routine for Encoder A
void encoderAInterrupt() {
  counterA++;
}
