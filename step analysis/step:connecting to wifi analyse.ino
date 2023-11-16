#include <ESP8266WiFi.h>//This is an Arduino library for ESP8266 WiFi modules to connect to WiFi networks.

const char* ssid     = "CE-Hub-Student";//WiFi network name
const char* password = "casa-ce-gagarin-public-service";//WiFi network password
const char* host = "iot.io";//The address of the host to be accessed

void setup() {
  Serial.begin(115200);//Start serial communication
  delay(100);

  // connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);//Check the WiFi connection status every 500 milliseconds
    Serial.print(".");//Print a dot to indicate a connection attempt
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

int value = 0;//Initialize an integer variable

//Attempt to connect to the HTTP port of a specified host
void loop() {
  delay(5000);
  ++value;
  //Increase the value variable every 5 seconds

  Serial.println("-------------------------------");
  Serial.print("Connecting to ");
  Serial.println(host);
  
  // Use WiFiClient class to create TCP connections
  WiFiClient client;//Create a WiFi client object
  const int httpPort = 80;//Set HTTP port to 80
  if (!client.connect(host, httpPort)) {//Attempt to connect to the specified host and port
    Serial.println("connection failed");
    return;
  }
  
  // We now create a URI for the request
  String url = "/index.html";//Set the URL path to be requested
  Serial.print("Requesting URL: ");
  Serial.println(host + url);
  
  // Use the client.print() method to send an HTTP GET request to the server
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +    //Send a GET request
               "Host: " + host + "\r\n" +    // Set the hostname
               "Connection: close\r\n\r\n"); //Set the connection options
  
  delay(500); //Wait 500 ms

  // Used to receive response data from the server and print it to a serial monitor
  while(client.available()){  
    //It's a loop that runs until the data received from the server is available. client.available() to check if there is data readable
    String line = client.readStringUntil('\r');
    //In each iteration, it reads a line of data returned from the server and stores it in a string called line
    Serial.print(line);
    //Print the line data to a serial monitor
  }

  delay(1000000);
  
}
