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
