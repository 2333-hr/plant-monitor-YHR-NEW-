#include <ESP8266WiFi.h>//This is an Arduino library for ESP8266 WiFi modules to connect to WiFi networks.
#include <ezTime.h>//This is a library that deals with time and time zones
#include <PubSubClient.h>//This is a library that implements MQTT client functionality

// Wifi and MQTT
#include "arduino_secrets.h" //A file that stores sensitive information


//Set up the credentials for the WiFi connection and MQTT client
const char* ssid     = SECRET_SSID;
const char* password = SECRET_PASS;
const char* mqttuser = SECRET_MQTTUSER;
const char* mqttpass = SECRET_MQTTPASS;


const char* mqtt_server = "mqtt.cetools.org";//Stores the address of the MQTT server.

WiFiClient espClient;//is a client object that is used to connect to Wi-Fi
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;

Timezone GB;


uint8_t soilPin = 0;   
int moisture_val;
int sensorVCC = 13;
int counter = 0;


#include <DHT.h>
#include <DHT_U.h>
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321

// DHT Sensor setup
uint8_t DHTPin = 12;        // on Pin 12 of the Huzzah
DHT dht(DHTPin, DHTTYPE);   // Initialize DHT sensor.    

void setup() {
  Serial.begin(115200);
  delay(100);

  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("10.129.118.162");
  Serial.println(WiFi.localIP());

  waitForSync();

  Serial.println("UTC: " + UTC.dateTime());
  

  GB.setLocation("Europe/London");
  Serial.println("London time: " + GB.dateTime());  

  // We setup an LED to be controllable via MQTT
  // Initialize the BUILTIN_LED pin as an output 
  // Turn the LED off by making the voltage HIGH
  pinMode(BUILTIN_LED, OUTPUT);     
digitalWrite(BUILTIN_LED, HIGH);  

client.setServer(mqtt_server, 1884);
client.setCallback(callback);

Serial.begin(115200);     //open serial port
  pinMode(sensorVCC, OUTPUT); 
  digitalWrite(sensorVCC, LOW);

  // open serial connection
  Serial.begin(115200);
  delay(100);

  // start DHT sensor
  pinMode(DHTPin, INPUT);
  dht.begin();
}

void loop() {
  delay(1000);
  Serial.println(GB.dateTime("H:i:s")); // UTC.dateTime("l, d-M-y H:i:s.v T")

   delay(5000);
  sendMQTT();

   counter++;
  if(counter> 6){      // change this value to set "not powered" time. higher number bigger gap
    // power the sensor
    digitalWrite(sensorVCC, HIGH);
    delay(1000);
    // read the value from the sensor:
    moisture_val = analogRead(soilPin);   // read the resistance      
    //stop power 
    digitalWrite(sensorVCC, LOW);  
    delay(100);
    
    Serial.print("sensor = " );                       
    Serial.println(moisture_val);     
    counter=0;    
  }  
  //wait
  Serial.print(".");                       
  delay(1000);

 Serial.print("Temp:");
  Serial.println(dht.readTemperature()); // Gets the values of the temperature
  Serial.print("Hum:");
  Serial.println(dht.readHumidity()); // Gets the values of the humidity
  delay(1000);
}


void sendMQTT() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  ++value;
  snprintf (msg, 50, "hello world #%ld", value);
  Serial.print("Publish message: ");
  Serial.println(msg);
  client.publish("student/CASA0014/plant/ucjtdjw", msg);
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {    // while not (!) connected....
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    
    // Attempt to connect
    if (client.connect(clientId.c_str(), mqttuser, mqttpass)) {
      Serial.println("connected");
      // ... and subscribe to messages on broker
      client.subscribe("student/CASA0014/plant/ucjtdjw/inTopic");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  // Switch on the LED if an 1 was received as first character
  if ((char)payload[0] == '1') {
    digitalWrite(BUILTIN_LED, LOW);   // Turn the LED on (Note that LOW is the voltage level
    // but actually the LED is on; this is because it is active low on the ESP-01)
  } else {
    digitalWrite(BUILTIN_LED, HIGH);  // Turn the LED off by making the voltage HIGH
  }

}
