int brightness = 0;
int potValue = 0;

void setup() {
  pinMode(9, OUTPUT);
}

void loop() {
  // read the value from the potentiometer (at pin A0)
  potValue = analogRead(A0);
  // scale the potentiometer voltage (a value between 0 - 1023)
  // to an applicable scale of brightness (0 - 255)
  brightness = map(potValue, 0, 1023, 0, 255);
  // Output this as a voltage to the LED (using PWM)
  analogWrite(9, brightness);
  delay(200); 
}
