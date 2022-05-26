# Boilerplate Arduino code for ESP8266 and ESP32 IoT devices 

Quickly configure ESP device code with Wifi, MQTT, OTA and voltage measurement (ESP8266 only for now)

Includes functions to feed sensor data to influxdb via telegraf (idb_publish, idb_publish_string)

Installation: Extract the zip in your arduino library folder or use the "add .ZIP library" command from the sketch menu

Usage: 
1. copy the espbp.ino file into a folder named espbp (or rename both)
2. set the #define switches to what you need
3. add your sensor specific code before and into the setup()
4. add your main code to loop()

MQTT_SUB:

Below loop() there is configuration for subscription to mqtt topics to control actions of your devices.
I use this to send IR codes to my audio equipment via MQTT. Could also be used to control relays for example.
There are two callback functions of which only one can be used. The other one needs to commented out or deleted. 

The first function uses message content as the trigger for an action

The second function lets you control actions by predefined topics, which leaves the option to use message content also

Battery:

On the ESP8266 the code uses the getVcc() function. If you set BATT 1 every loop() will measure the voltage and publish in influxdb/telegraf format.
Take a look at the espbp_loop() function in espbp.h

On the ESP32 getVcc() or similar does not exist. You have to use one of the many ADC, probably in combination with a voltage devider. The code in battery.h shows how I did this in the past for all devices before I discovered getVcc().

