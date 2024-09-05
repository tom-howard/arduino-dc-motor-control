const byte hallSensorPin = 2;
volatile long counter = 0;

void setup() {
  Serial.begin(9600);
  pinMode(hallSensorPin, INPUT);
  attachInterrupt(
    digitalPinToInterrupt(hallSensorPin),
    magnetInterrupt,
    FALLING
  );
}

void loop() {
  if (millis() % 1000 == 0) {
    // Do this every ~1000 ms:
    Serial.print(counter);
    Serial.println(" magnet interrupt(s) detected");
    delay(10);
  }
}

// Interrupt routine executes every time the 
// magnet is detected by the Hall-effect sensor 
void magnetInterrupt() {
  counter++;
}
