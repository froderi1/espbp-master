#define DEVICE_NAME "espbp_device"
#define SERIAL_BAUD 115200
#define MQTT_SERVER "test.mosquitto.org"

#define BATT  1   // ESP8266 only | ESP32 use ADC and something like battery.h
#define MQTT  1
#define MQSUB 0

char* topic = "espbp_topic";
//const String topic = "espbp_topic";
const String measurement = "iot_measurement";

#define OTA   1
// OTA doesn't work with deep sleep. You can use a dedicated pin that if pulled low
// makes the device go into a OTA-handle loop
// make sure the pin is capable of input and has pullup (GPIO 0-15 on esp8266)
// defining an OTAPIN overrides the normal code that comes with OTA 1  
//#define OTAPIN 14  

#define uS_TO_S_FACTOR 1000000ULL   /* Conversion factor for micro seconds to seconds */
#define TIME_TO_SLEEP  5            /* duration of deep sleep in seconds */

#include <espbp.h>

void setup()
{
  fhr_setup();

  // additional setup code here

}

void loop()
{
  fhr_loop();

  // your main code here

  #if (MQTT)
    idb_publish(topic, measurement, DEVICE_NAME, "Seconds passed", millis()/1000);
  #endif

  delay(1000);  // avoid timing issue with mqtt client
  //esp_deep_sleep_start();               //ESP32
  //ESP.deepSleep(TIME_TO_SLEEP * uS_TO_S_FACTOR);  //ESP8266 
  delay(9000);
}

#if (MQSUB)

// pick one of the two callback functions

// Function 1: Control action by message  
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
  payload[length] = '\0';
  String message = String((char*)payload);
  // Delays need to be done on publisher side
  if (message == "message1")  {
    // do stuff
  }
  if (message == "message2")  {
    // do other stuff
  }
  if (message == "message3")  {
    // do other stuff
  }
}

// function 2: Control actions by topic

#define S_TOPIC_1 "s_topic_1" 
#define S_TOPIC_2 "s_topic_2" //add more if needed and 
#define S_TOPIC_3 "s_topic_3" //change callback function

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
  payload[length] = '\0';
  String message = String((char*)payload);
  
  if (strcmp(topic,S_TOPIC_1)==0){
    // whatever you want for this topic
    Serial.println("received T1");
    Serial.println(message);
  }
 
  if (strcmp(topic,S_TOPIC_2)==0) {
    // obvioulsy state of my red LED
    Serial.println("received T2");
    Serial.println(message);
  }
 
  if (strcmp(topic,S_TOPIC_3)==0) {
    // this one is blue...
    Serial.println("received T3");
    Serial.println(message);
  }  
 
  if (strcmp(topic,"green")==0) {
    // i forgot, is this orange?
  }  
}
#endif
