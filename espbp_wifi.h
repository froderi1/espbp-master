#if defined(ESP8266)
  #include <ESP8266WiFi.h>
#elif defined(ESP32)
  #include <WiFi.h>  // ESP32
#endif

#include <wifi_cred.h>

void setup_wifi() {

  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(SSID);

  #if defined(ESP8266)
   #ifdef DEVICE_NAME
    WiFi.hostname(DEVICE_NAME);
   #endif
  #endif
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(SSID, PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}
