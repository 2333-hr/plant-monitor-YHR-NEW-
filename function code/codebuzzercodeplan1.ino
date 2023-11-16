//selected
const int soilSensorPin = A0;  // Soil moisture sensor connected to analog input pin A0
const int buzzerPin = 16;      // Buzzer connected to digital output pin 16
const int thresholdValue = 300;  // Set moisture threshold

void setup() {
  pinMode(buzzerPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int soilMoisture = analogRead(soilSensorPin);

  if (soilMoisture ＞ thresholdValue) {
    // Trigger the buzzer when soil moisture is below the threshold
    digitalWrite(buzzerPin, HIGH);
    delay(1000);  // Delay for 1 second
    digitalWrite(buzzerPin, LOW);
    
  }

  // Output moisture value to the serial monitor
  Serial.print("Soil Moisture: ");
  Serial.println(soilMoisture);
  delay(1000);  // Read every 1 second
}
