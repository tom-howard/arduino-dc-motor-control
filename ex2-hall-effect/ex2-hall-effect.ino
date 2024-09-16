const byte hallSensorPin = 2;
volatile long counter = 0;
// Some variables for controlling code execution rates:
unsigned long timestamp = millis();
unsigned long elapsed = 0;

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
  elapsed = millis() - timestamp;
  if (elapsed > 1000) {
    // Do this every ~1000 ms:
    Serial.print(counter);
    Serial.println(" magnet interrupt(s) detected");
    timestamp = millis(); // Reset the timestamp
  }
}

// Interrupt routine executes every time the 
// magnet is detected by the Hall-effect sensor 
void magnetInterrupt() {
  counter++;
}
