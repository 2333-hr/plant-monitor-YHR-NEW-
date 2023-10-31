# plant-monitor-YHR-NEW-
connected environment
Some important notes in advance:
I've created a library before, but because it's all uploaded in the form of folders, I feel that the presentation form is not intuitive and I want to rebuild some architecture, so I simply build a new library. 
Here are some pictures of the proof:

<img width="697" alt="843c34ac0b1acea324bfd42f3878627" src="https://github.com/2333-hr/plant-monitor-YHR-NEW-/assets/146243657/76391445-8c19-4699-b368-1ea1de9e9db3">
<img width="1244" alt="80c2ab1ab238e87d12a1c4f053d4096" src="https://github.com/2333-hr/plant-monitor-YHR-NEW-/assets/146243657/4d42e8ad-f28b-4f77-b448-e40faa6dd649">

Now let's get started with a note about my library! Hope to help others have a better understand of the content of the files in my Github repository and its related features!


1. Explanation of file contents about the library
   
① First, the code of some steps of the plant monitor (I've selected steps that I think are somewhat difficult) were analyzed in detail, and the file was named "step: xxxanalyse". (Two are currently analyzed, and if there is a need for improvement, I will continue to analyze and upload the files).

② Regarding the final code of the workshop "plant monitor" step 1-9 function, "STEP9" is the integration code provided by the teacher in the ninth step. I have changed or added some comments. "mixed1-8" is my own mixed steps. The merged codes in 1-8 have similar functions. They are both used for the development of the ESP8266 board, connecting to the WiFi network, reading the temperature and humidity data of the DHT22 sensor, transmitting the data through MQTT and setting up a Web server. But there are also subtle differences. Later, I may need to select and integrate them into a final version of the optimal document.

The specific differences are as follows:
1. "mixed1-8" uses the ezTime library to handle time and time zones, while "STEP9" does not use this library.

2. The code structure is slightly different. "mixed1-8" uses a function called waitForSync, while "STEP9" does not. The purpose of this function is to wait for time synchronization to ensure that the device's time is accurate. In "STEP9", time synchronization seems to be done through GB objects, but there is no explicit synchronization function.

3. In the sendMQTT function, "mixed1-8" uses the %.1f and %.0f format strings when publishing temperature and humidity data to the MQTT topic, which can limit the number of decimal places. "STEP9" has no such restrictions.

4. "mixed1-8" uses the startWifi(), startWebserver() and syncDate() functions to initialize the WiFi connection, Web server and time synchronization. "STEP9" places these initialization operations directly in the setup() function without using a separate initialization function.

5.The HTML generation function SendHTML of "5.mixed1-8" contains more HTML code and displays the sampling time. The HTML in "STEP9" is relatively simple.

③About the new function code (part of the code form). Use "LEDcode" to name The code file for the LED to turn on and off based on the soil moisture value; use "buzzercodePLAN1/2" to name the code file for whether to emit a beep based on the soil moisture value.

④ About the final plant monitor code (completed code form) that adds personal ideas: it is currently a file named "plant monitor-justaddLEDcod". This file only adds the LED flash alarm code based on the workshop "plant monitor". That's because the buzzer is currently used up, and the buzzer will be connected later. The code to make the buzzer run will also be added to the final code according to the plan --------let's look forward to it!


2. What has been done so far (progress)
Connect to wifi using Feather HUZZAH ESP8266;
Get time from NTP server on internet using ezTime library;
Publish data to MQTT server;
Watch TOPIC using MQTT Explorer;
Learn to solder and solder the circuit board, Feather HUZZAH ESP8266 board, resistor, and DHT22 temperature/humidity sensor together, and then use nails and wires to connect the sensor and the nails so that the sensor can detect temperature and humidity through the nails;
Connect wifi and MQTT to send soil data to MQTT;
Set the Raspberry Pi as the gateway, burn the SD card to the Raspberry Pi, install InfluxDB, Telegraf and Grafana to achieve data visualization.
Raspberry Pi related screenshots:
<img width="1244" alt="ad033bf2725da3a2bf83e36ff5fe724" src="https://github.com/2333-hr/plant-monitor-YHR-NEW-/assets/146243657/00de55cc-8bdc-47df-ba32-328e964036ad">
<img width="1244" alt="320510e04f1bcd33af70a472b6268a7" src="https://github.com/2333-hr/plant-monitor-YHR-NEW-/assets/146243657/5b57b615-8a0c-48f9-9fbd-51e2ddc02950">


3. Regarding the final goal of plant monitor
Based on the basic functions of the workshop, I plan to make a plant monito that can reflect the state of the plant through light (LED) and sound. When the soil moisture is lower than a certain value (currently set to 300 for LED flashing observed), the light will flash and a sound will sound at the same time to remind people to water. At the same time, plant status data is displayed to some device screens to detect the status of plants in real time.


4. How to realize the new function of ideal plant monitor?
①About the implementation principle of LED light response: (already completed)
Write a piece of Arduino code (file "LEDcode") and add it to the original workshop code to connect the positive (long pin) of the LED to digital pin 13 of the Feather HUZZAH ESP8266. Before connecting, make sure the power is off. The negative (short pin) of the LED is usually connected to the ground (GND) pin, make sure to connect the negative of the LED to the GND pin of the Feather HUZZAH ESP8266 for functionality.

② Regarding the implementation principle of sound response: (to do list)
Plan 1: 
Connect soil moisture sensor and buzzer to Arduino. Make sure to connect the sensor's data pin to one of the Arduino's analog input pins and the buzzer or speaker to one of the digital output pins. The sensor and buzzer need to be grounded. Use Arduino IDE to write a program to read the value of the soil moisture sensor. When the value is lower than a certain value, trigger the buzzer or speaker to make a sound. When the soil moisture is lower than thresholdValue, the buzzer will be triggered and sound. (plan1)
Plan 2:
1.Process the received MQTT message:
2.Process the received MQTT message in the callback function and compare the humidity data in the message with the threshold.
If the humidity is below the threshold, trigger the buzzer, otherwise turn off the buzzer.
Upload code:
3.Upload the written Arduino code to the Arduino Uno board.
4 Monitor data: Monitor the data from the MQTT server and control the buzzer based on the received humidity data.

③ About displaying plant status data to some device screens: (to do list)
Install serial port data receiving software on your computer, such as CoolTerm (for Windows and macOS), and open the serial port data receiving software. Select the correct serial port and baud rate in the software, this information is the same as in the serial monitor. Start the serial port data reception, and then you will see the numbers sent from the Arduino in the software.

5. How can others view my plant monitor data or how others can access the information being generated from your plant ?(how do we know it is your plant?)
Under the same LAN, the others can view it through MQTT according to the path student/CASA0014/plant/ucxxx. Each person's name is unique. You can view temperature/humidity/moisture.
<img width="416" alt="image" src="https://github.com/2333-hr/plant-monitor-YHR-NEW-/assets/146243657/fb6d43c2-2f9c-437d-98ae-72ceaefd4cba">

Or others can log in to my telegraf/Grafana to view it, provided that it is under the same LAN and I enter my username and password to log in and view it.


6. Problems encountered in the workshop
①Problems encountered during soldering

The board was not used when soldering the circuit board, which caused the circuit board to be skewed. The teacher helped to straighten the connection by soldering and melting it again, and the circuit board and Feather HUZZAH ESP8266 were connected.
![029ab8b0799274a54308135cb0b97a3](https://github.com/2333-hr/plant-monitor-YHR-NEW-/assets/146243657/bdb1e5a1-69f4-4a81-93c5-6163e797801a)

②Problems encountered when connecting to Raspberry Pi

The Raspberry Pi could not connect to wifi on my own computer and the connection was refused. With the help of the teacher, I used the local ssh on the laboratory computer to connect to the wifi network.

