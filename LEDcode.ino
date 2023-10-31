const int soilPin = A0; // Analog pin for connecting the soil moisture sensor
const int ledPin = 13;  // Digital pin for connecting the LED
int threshold = 30;    // Moisture threshold, adjust based on sensor readings

void setup() {
  pinMode(soilPin, INPUT);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  int moisture = analogRead(soilPin);

  if (moisture < threshold) {
    // When soil moisture is below the threshold, blink the LED
    digitalWrite(ledPin, HIGH);  // Turn on the LED
    delay(500);                 // Delay for half a second
    digitalWrite(ledPin, LOW);   // Turn off the LED
    delay(500);                 // Delay for half a second
  } else {
    // When soil moisture is above or equal to the threshold, turn off the LED
    digitalWrite(ledPin, LOW);
    delay(1000);  // Delay for one second
  }
}
