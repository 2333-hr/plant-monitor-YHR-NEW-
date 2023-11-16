// Include necessary libraries for WiFi and sensor functionality
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ezTime.h>
#include <PubSubClient.h>
#include <DHT.h>
#include <DHT_U.h>

// Define the type of the DHT sensor
#define DHTTYPE DHT22   // DHT 22 (AM2302, AM2321)

// Define pin numbers and initialize variables for sensors
uint8_t DHTPin = 12;        // DHT sensor connected to pin 12
uint8_t soilPin = 0;        // Soil moisture sensor connected to ADC pin (A0)
float Temperature;          // Variable to store temperature value
float Humidity;             // Variable to store humidity value
int Moisture = 1;           // Initial moisture value
int sensorVCC = 13;         // Power supply pin for the soil moisture sensor
int blueLED = 2;            // Pin number for the blue LED
DHT dht(DHTPin, DHTTYPE);   // Initialize DHT sensor object

// WiFi and MQTT configuration
#include "arduino_secrets.h" // Include file with sensitive data
const char* ssid     = SECRET_SSID;     // WiFi SSID
const char* password = SECRET_PASS;     // WiFi password
const char* mqttuser = SECRET_MQTTUSER; // MQTT username
const char* mqttpass = SECRET_MQTTPASS; // MQTT password

// Initialize web server and MQTT client
ESP8266WebServer server(80);            // Web server on port 80
const char* mqtt_server = "mqtt.cetools.org"; // MQTT server address
WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;                       // Variable to store the last message time
char msg[50];                           // Buffer to store the message
int value = 0;                          // General purpose value variable

// Timezone configuration
Timezone GB;                            // Timezone object for Great Britain

// Setup function to initialize components
void setup() {
  // LED setup
  pinMode(BUILTIN_LED, OUTPUT);         // Set the built-in LED as output
  digitalWrite(BUILTIN_LED, HIGH);      // Turn off the LED (active low)

  // Soil sensor and blue LED setup
  pinMode(sensorVCC, OUTPUT);           // Set sensor VCC as output
  digitalWrite(sensorVCC, LOW);         // Turn off sensor power
  pinMode(blueLED, OUTPUT);             // Set blue LED as output
  digitalWrite(blueLED, HIGH);          // Turn off the blue LED

  // Initialize serial communication for debugging
  Serial.begin(115200);
  delay(100);

  // Start DHT sensor
  pinMode(DHTPin, INPUT);               // Set DHT sensor pin as input
  dht.begin();                          // Begin DHT sensor

  // Start WiFi and web server
  startWifi();
  startWebserver();
  syncDate();                           // Synchronize date and time

  // Start MQTT server
  client.setServer(mqtt_server, 1884);  // Set MQTT server and port
  client.setCallback(callback);         // Set MQTT callback function
}

// Main loop function
void loop() {
  // Handle web server requests
  server.handleClient();

  // Read and send sensor data every minute
  if (minuteChanged()) {
    readMoisture();                     // Read moisture data
    sendMQTT();                         // Send data via MQTT
    Serial.println(GB.dateTime("H:i:s")); // Print current time
  }
  
  // Maintain MQTT connection
  client.loop();
}

// Function to read soil moisture
void readMoisture(){
  // Power the sensor and read moisture level
  digitalWrite(sensorVCC, HIGH);       // Turn on sensor power
  digitalWrite(blueLED, LOW);          // Turn on the blue LED
  delay(100);                          // Wait for sensor stabilization
  Moisture = analogRead(soilPin);      // Read soil moisture value
  digitalWrite(sensorVCC, LOW);        // Turn off sensor power
  digitalWrite(blueLED, HIGH);         // Turn off the blue LED
  delay(100);                          // Wait before next reading
  Serial.print("Wet ");                // Debug print
  Serial.println(Moisture);            // Print moisture value
}

// Function to start WiFi connection
void startWifi() {
  // Connect to WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  // Wait until connected
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial
