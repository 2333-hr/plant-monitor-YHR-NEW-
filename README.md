# plant-monitor-YHR-NEW-
Now let's get started with a note about my library! Hope to help others have a better understand of the content of the files in my Github repository and its related features!

# Explanation of file contents about the library
## In this project, my code is mainly divided into three parts. 
### The first part is in the "step analysis" folder, which is the code analysis of each step of the work shop (it is only a functional analysis, so viewers can understand that it cannot be run alone). 
### The second part is the "function code" folder, which contains the added function code and can be used as a template. 
### The third part is the final code of the plant monitor, named "plant monitor final".

# About my plants
When it comes to plant monitors, plants are the monitoring body of the monitor. The plant I chose in this project is Yushu, which is a common indoor landscape ornamental plant. The suitable growth temperature was 20 – 30℃ and over 38℃. When slow growth or into a short dormancy, the temperature as low as 0℃ will be frozen death. Yushu is suitable for growing in high humidity soil, the relative humidity of 60% -80% is appropriate. Since the soil temperature of plants is about equal to the room temperature, Yushu is more suitable for survival at the normal room temperature, so I chose to only monitor the soil humidity of plants. Note that in the device code setting, there are two humidity readings, one of which is the relative humidity of the air read from the DHT 22 sensor in percentage (%), indicating the proportion of water vapor in the air relative to the maximum possible content. The other is the soil moisture read from the soil moisture sensor in the original value of the simulated reading, which depends on the specific sensor and setting. For most soil moisture sensors, this value is not a percentage, but a reading based on the resistance or conductivity change of the sensor. This analog reading is typically a number between 0 and 1023 (for most Arduino boards, they have a 10-digit analog-to-digital converter). This reading reflects the relative change in resistance between nails rather than the direct humidity percentage. High reading (near 1023) usually indicate low humidity (high resistance). Low reading (close to 0) indicates high humidity (low resistance). However, this number change is non-linear, and it is difficult to accurately express it. Based on the appropriate humidity required for the growth of Yushu is high, so I set the moisture value roughly to 300.

# List of main materials
Adafruit Huzzah ESP8266 WiFi；Integrated circuit board；Raspberry Pi；Two nails and open wires；DHT22 temperature / humidity sensor；LED；Buzzer

## function
### Adafruit Huzzah ESP8266 WiFi: 
Connect to the specified WIFI and transfer data to MQTT server; use ezTime library for time synchronization to obtain real-time date and time information for monitoring plant temperature and humidity; connect with USB interface as power supply, provide pins including ground pins. A simple Web server is set up to access the IP address and display the temperature and humidity sensors of the DHT 22 sensor. Real-time sensor data can be obtained through the Web page.
### Circuit board: 
Integrate the ESP board with two nails and DHT 22 sensors
### Raspberry Pi: 
Receiving plant monitor data as a gateway and install InfluxDB, Telegraf and Grafana on the Raspberry Pi end.
### Two nails and open wires: 
Wire: as a soil resistance sensor, the change of water temperature in the soil affects its resistivity. Usually, as the temperature increases, the conductivity increases, and the increase of soil humidity usually leads to the decrease of soil resistance.
### DHT22 temperature / humidity sensor: 
Read the soil temperature and humidity.
### LED: 
The LED flashes as a prompt when the moister is higher than 300.
### Buzzer: 
When the moister is higher than 300, buzzer plays music as a prompt.


# The basic work part of the workshop
### 1.Connecting to Wifi
### 2.Getting the time
### 3.Publish data to an MQTT server

![61d9b487f91f93c23a268c017c0804d](https://github.com/2333-hr/plant-monitor-YHR-NEW-/assets/146243657/1cbfd9ae-31ce-4f2c-9b84-066509e68ade)

### 4.Using MQTT Explorer to watch a TOPIC
<img width="770" alt="0c1246d1a7f2cd05ba0f4c118fd1c95" src="https://github.com/2333-hr/plant-monitor-YHR-NEW-/assets/146243657/6b912dc9-2931-4e76-9507-b9b86ffcccb3">

### 5.Sensing Soil + the environment
<img width="519" alt="86ab213cf1a012ead677a1fb7ca06a4" src="https://github.com/2333-hr/plant-monitor-YHR-NEW-/assets/146243657/0329e33c-2651-48e7-ad12-0e0b9a3581ca">
<img width="520" alt="8cc475d8f88741dc3312a68ddc2de90" src="https://github.com/2333-hr/plant-monitor-YHR-NEW-/assets/146243657/45549250-22b1-48b6-92e1-4981ea6ebe3e">

### 6.Sending Soil Data to MQTT
![b383f76873bc38eb14e160d163dc601](https://github.com/2333-hr/plant-monitor-YHR-NEW-/assets/146243657/72c3fb8d-4cd9-48d2-88ea-b00394d09d80)

### 7.Setting up a RPi as a gateway
### 8.Downloading InfuxDB/Telegraf/Grafana and implement data visualization

# Regarding the final goal of plant monitor
Based on the basic functions of the workshop, I plan to make a plant monito that can reflect the state of the plant through light (LED) and sound. When the soil moisture is lower than a certain value (currently set to 300 for LED flashing observed), the light will flash and a sound will sound at the same time to remind people to water. At the same time, plant status data is displayed to some device screens to detect the status of plants in real time.


# How to realize the ideal plant monitor?
## About the implementation principle of LED light response: 
Write a piece of Arduino code (file "LEDcode") and add it to the original workshop code to connect the positive (long pin) of the LED to digital pin 13 of the Feather HUZZAH ESP8266 by soldering. Before connecting, make sure the power is off. The negative (short pin) of the LED is usually connected to the ground (GND) pin, make sure to connect the negative of the LED to the GND pin of the Feather HUZZAH ESP8266 for functionality.

## Regarding the implementation principle of sound response: 
### Plan 1: (selected)
Use the ESP board as the power supply, directly solder the buzzer on the ESP board (pin 16 and ground pin), and control the buzzer through the Arduino code so that when the moister value is higher than 300, that is, when the soil moisture is lower than a certain value A buzzer plays music to remind people to water.
### Plan 2:
1.Process the received MQTT message:
2.Process the received MQTT message in the callback function and compare the humidity data in the message with the threshold.
If the humidity is below the threshold, trigger the buzzer, otherwise turn off the buzzer.
Upload code:
3.Upload the written Arduino code to the Arduino Uno board.
4 Monitor data: Monitor the data from the MQTT server and control the buzzer based on the received humidity data.

## About displaying plant status data to some device screens:
Install serial port data receiving software on your computer, such as CoolTerm (for Windows and macOS), and open the serial port data receiving software. Select the correct serial port and baud rate in the software, this information is the same as in the serial monitor. Start the serial port data reception, and then you will see the numbers sent from the Arduino in the software.

# Plant monitor display

![df0d9c531c61df8c08bbe1e6a81c0b5](https://github.com/2333-hr/plant-monitor-YHR-NEW-/assets/146243657/cff0b419-82f2-4efa-b79b-de0e7f3a5241)

https://github.com/2333-hr/plant-monitor-YHR-NEW-/assets/146243657/6ea0d840-fbbc-4d67-9b07-3d53422c5376

https://github.com/2333-hr/plant-monitor-YHR-NEW-/assets/146243657/6d377b32-f2cb-4ad2-ba0b-9e8da9840afc

# Data display
<img width="602" alt="a61cfe42b01e994dae3a321bdd16e1f" src="https://github.com/2333-hr/plant-monitor-YHR-NEW-/assets/146243657/1cbf5ecd-64a4-47a1-8648-fd5db8285eda">
<img width="1244" alt="44d52721e582859d96c27d09b6f021d" src="https://github.com/2333-hr/plant-monitor-YHR-NEW-/assets/146243657/6c876e2c-2a76-4c63-8602-9dc39c35445b">
<img width="1244" alt="69a61e385ef23344f455dddd6f8d9a3" src="https://github.com/2333-hr/plant-monitor-YHR-NEW-/assets/146243657/34ee0693-c64f-4e4a-9ccd-fbaeb9c192fc">
<img width="1244" alt="29b1df79a79e52ee4a75a05f346b474" src="https://github.com/2333-hr/plant-monitor-YHR-NEW-/assets/146243657/a890b6d7-3007-41c6-bfc3-e801432d61af">


# How can others view my plant monitor data or how others can access the information being generated from my plant ?(how do you know it is my plant?)
   
Under the same LAN, the others can view it through MQTT according to the path student/CASA0014/plant/ucxxx. Each person's name is unique. You can view temperature/humidity/moisture.

<img width="416" alt="image" src="https://github.com/2333-hr/plant-monitor-YHR-NEW-/assets/146243657/fb6d43c2-2f9c-437d-98ae-72ceaefd4cba">

Or others can log in to my telegraf/Grafana to view it, provided that it is under the same LAN and I enter my username and password to log in and view it.

# Problems encountered in the workshop
   
①Problems encountered during soldering

The board was not used when soldering the circuit board, which caused the circuit board to be skewed. The teacher helped to straighten the connection by soldering and melting it again, and the circuit board and Feather HUZZAH ESP8266 were connected.
![029ab8b0799274a54308135cb0b97a3](https://github.com/2333-hr/plant-monitor-YHR-NEW-/assets/146243657/bdb1e5a1-69f4-4a81-93c5-6163e797801a)

②Problems encountered when connecting to Raspberry Pi

The Raspberry Pi could not connect to wifi on my own computer and the connection was refused. With the help of the teacher, I used the local ssh on the laboratory computer to connect to the wifi network.

③Encountered problems when visualizing data

The data could not be obtained through MQTT in Telegraf, and it was later discovered that the API TOKEN was entered incorrectly. The Raspberry Pi configuration principle is to input a Raspberry Pi data to obtain TOKEN and an MQTT data to obtain TOKEN, but I only entered the Raspberry Pi data to obtain TOKEN. At the same time, many students had the same problem. In the final analysis, it is about the code structure. Caused by unfamiliarity with the function.

# Reflection
   
In the process of doing workshops, you often encounter many problems when piecing together the code step by step. Most of the problems are caused by a lack of understanding of the code structure and functions as well as writing rules. Therefore, I think we should consolidate the foundation, in addition to what is taught in class. In addition to learning knowledge, you must also clearly understand the relevant basic rules, otherwise it will easily cause the problem of not knowing the specific meaning of the code. So for some steps, I conducted a line-by-line analysis, and also wanted to learn more about some basic code running rules through example analysis.

Some important notes in advance:
I've created a library before, but because it's all uploaded in the form of folders, I feel that the presentation form is not intuitive and I want to rebuild some architecture, so I simply build a new library. 
Here are some pictures of the proof:

<img width="697" alt="843c34ac0b1acea324bfd42f3878627" src="https://github.com/2333-hr/plant-monitor-YHR-NEW-/assets/146243657/76391445-8c19-4699-b368-1ea1de9e9db3">
<img width="1244" alt="80c2ab1ab238e87d12a1c4f053d4096" src="https://github.com/2333-hr/plant-monitor-YHR-NEW-/assets/146243657/4d42e8ad-f28b-4f77-b448-e40faa6dd649">


What impressed me most was that during the welding process, I had a big problem. First of all, it was because I did not fully follow the workshop instructions and did not use board fixation when welding the circuit board, which resulted in a serious distortion of the gate welding. The circuit board and the Feather HUZZAH ESP8266 board could not be spliced. My first thought at the time was to change the board and re-solder it. I was quite anxious. However, when I asked the professor, he said that it could be changed by soldering without re-soldering. I was relieved. Although I encountered many problems in the plant monitor workshop, these problems also taught me a lot. In addition to the code, I also need to be calm when encountering problems and actively look for solutions instead of panicking and being overwhelmed.
