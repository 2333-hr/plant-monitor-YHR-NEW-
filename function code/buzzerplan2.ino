#include <SPI.h>
#include <Ethernet.h>  // If using an Ethernet module
#include <PubSubClient.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };  // Assign a MAC address based on your module
EthernetClient ethClient;
PubSubClient client(ethClient);

int buzzerPin = 7;  // Pin connected to the buzzer
int threshold = 400;  // Humidity threshold, adjust based on sensor readings

void callback(char* topic, byte* payload, unsigned int length) {
  // Handle received MQTT messages
  float humidity = atof((char*)payload);
  if (humidity < threshold) {
    // Trigger the buzzer when soil humidity is below the threshold
    tone(buzzerPin, 1000);  // Start the buzzer with a 1000Hz tone
  } else {
    noTone(buzzerPin);  // Turn off the buzzer
  }
}

void setup() {
  Ethernet.begin(mac);
  client.setServer("mqtt_server_address", 1883);  // Set MQTT server address and port
  client.setCallback(callback);
  pinMode(buzzerPin, OUTPUT);  // Set the buzzer pin as an output
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}

void reconnect() {
  while (!client.connected()) {
    if (client.connect("arduino-client")) {
      client.subscribe("topic_name");  // Subscribe to the MQTT topic
    } else {
      delay(5000);
    }
  }
}
