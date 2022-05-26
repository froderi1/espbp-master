#include <espbp_wifi.h>
#if ( OTA )
   #include <espbp_OTA.h>
#endif
#if ( MQTT ) 
   #include <espbp_mqtt.h>
#endif

#if ( MQSUB )
  // Callback function header
  void callback(char* topic, byte* payload, unsigned int length);
#endif

#if ( BATT )
   #if defined(ESP8266)
      ADC_MODE(ADC_VCC)
      uint16_t batterylevel = 0;
   #endif  
#endif

void fhr_setup(){

  Serial.begin(SERIAL_BAUD);
  while(!Serial) {} // Wait
    
  setup_wifi();
  
  #if ( OTA )
    OTA_setup();
  #endif
  
  #if defined(ESP32)
     esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
  #endif


  #if ( MQTT ) 
    client.setServer(MQTT_SERVER, 1883);
    #if (MQSUB)
      client.setCallback(callback);
    #endif
    publish_identity();
  #endif

  #if defined (OTAPIN)
    pinMode(OTAPIN, INPUT_PULLUP);
    Serial.println(digitalRead(OTAPIN));
  #endif

}

void fhr_loop(){
   #if ( MQTT ) 
      if (!client.connected()) {
         reconnect();
      }
      client.loop();
   #endif

   #if ( BATT )
      #if defined(ESP8266)
         batterylevel = ESP.getVcc();
         idb_publish(topic, "battery", DEVICE_NAME, "voltage", batterylevel / 1000.0);
      #endif
   #endif

   #if defined (OTAPIN)
      Serial.print("otaPin State: ");
      Serial.println(digitalRead(OTAPIN));
      while (!digitalRead(OTAPIN)) {
         Serial.print("otaPin State (loop): ");
         Serial.println(digitalRead(OTAPIN));
         ArduinoOTA.handle();
         delay(500);
      }
   #else
      #if defined (OTA)
         ArduinoOTA.handle();
      #endif
   #endif
}
