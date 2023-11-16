#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// sensitive information stored
#include "arduino_secrets.h" 

//Set up credentials for Wi-Fi and MQTT
#define SECRET_SSID "ssid name"
#define SECRET_PASS "ssid password"
#define SECRET_MQTTUSER "user name - eg student"
#define SECRET_MQTTPASS "password";
 

//Define Wi-Fi and MQTT-related variables
const char* ssid     = SECRET_SSID;   
const char* password = SECRET_PASS;
const char* mqtt_server = "mqtt.cetools.org";

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;

//Set up the Wi-Fi connection, MQTT connection, and other configurations when the Arduino starts
void setup() {

  // We setup an LED to be controllable via MQTT
  // Initialize the BUILTIN_LED pin as an output 
  // Turn the LED off by making the voltage HIGH
  pinMode(BUILTIN_LED, OUTPUT);     
  digitalWrite(BUILTIN_LED, HIGH);  

  // open serial connection via the wifi to the mqtt broker
  Serial.begin(115200);
  delay(100); // to give time for the serial connection to open

  // Initiate the connecting to wifi routine
  startWifi();

  // Once connected to wifi establish connection to mqtt broker
  client.setServer(mqtt_server, 1884);
  
  // The callback in this case listens for instructions to 
  // change the state of the LED - here we are initialising 
  // that function
  //The callback function callback is set up to process messages received from the MQTT broker. 
  //The callback function listens for messages to control the LED state
  client.setCallback(callback);

}

//
void loop() {
  delay(5000);
  sendMQTT();//Used to connect to the MQTT broker and send messages
}


// This function is used to set-up the connection to the wifi
// using the user and passwords defined in the secrets file
// It then prints the connection status to the serial monitor

//starWifi Make sure that the Arduino is connected to a Wi-Fi network before starting the main operation, 
//as MQTT usually requires a network connection to work properly
void startWifi(){
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  // check to see if connected and wait until you are
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

// This function is used to make sure the arduino is connected
// to an MQTT broker before it tries to send a message and to 
// keep alive subscriptions on the broker (ie listens for inTopic)

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {    // while not (!) connected....
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    //Make sure you have a unique identifier every time you connect. 
    //This can help ensure that there are no duplicate connection issues
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
////Make sure that the Arduino is connected to the MQTT broker in order to send and receive MQTT messages.
// If the connection is lost, the function will attempt to re-establish the connection to maintain the continuity of communication.

// This function sends (publishes) a message to a MQTT topic
// once a connection is established with the broker. It sends
// an incrementing variable called value to the topic:
// "student/CASA0014/plant/ucjtdjw"




//Used to publish (send) a message to an MQTT topic. 
void sendMQTT() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  //code calls the MQTT client's loop function to ensure that the MQTT connection remains active and processes incoming messages.
  ++value; //Increment an integer variable value, which is used to generate the ordinal number in the message
  snprintf (msg, 50, "hello world #%ld", value);
  //Stores the content of messages that will be published to MQTT topics
  Serial.print("Publish message: ");
  Serial.println(msg);
  //Prints the message to be published in the serial monitor for debugging and tracing purposes
  client.publish("student/CASA0014/plant/ucjtdjw", msg);
}

// The callback function is called when an incoming message is received
// from the MQTT broker (ie the inTopic message)/ In this demo if the first
// character of the message has the value "1" we turn an LED on. Any other value 
// results in the LED being turned off

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++)
  //A loop that iterates through each byte of the received message content
   {
    Serial.print((char)payload[i]);
    //Used to print each byte in the message content
  }
  Serial.println();
  //Lets you print a line break after the message content is printed, so that the next message content starts on a new line

    // Switch on the LED if an 1 was received as first character
  if ((char)payload[0] == '1') 
  {
    digitalWrite(BUILTIN_LED, LOW);   // Turn the LED on (Note that LOW is the voltage level
    // but actually the LED is on; this is because it is active low on the ESP-01)
  } else {
    digitalWrite(BUILTIN_LED, HIGH);  // Turn the LED off by making the voltage HIGH
  }

}
