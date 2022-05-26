#include <PubSubClient.h>

WiFiClient espClient;
PubSubClient client(espClient);

void publish_identity(){
  String payload;
  payload = DEVICE_NAME;
  payload += " IP:";
  payload += WiFi.localIP().toString();
  client.publish("Device: ", (char*) payload.c_str());
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = DEVICE_NAME;
    clientId += "_";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
  
  if (MQSUB) {
    #ifdef S_TOPIC_1
      client.subscribe(S_TOPIC_1);
    #endif
    #ifdef S_TOPIC_2
      client.subscribe(S_TOPIC_2);
    #endif
    #ifdef S_TOPIC_3
      client.subscribe(S_TOPIC_3);
    #endif
  }
  
  publish_identity();
}

void idb_publish(char* topic, String measurement, String devicename, String value_type, float value) {
  String payload;
  payload = measurement;
  payload += ",device=";    // influxDB Measurement,Tag
  payload += devicename;
  payload += " ";
  payload += value_type;
  payload += "=";
  payload += value;
  client.publish(topic, (char*) payload.c_str());
  Serial.println(payload);
}


void idb_publish_string(char* topic, String measurement, String devicename, String value_type, String value) {
  String payload;
  payload = measurement;
  payload += ",device=";    // influxDB Measurement,Tag
  payload += devicename;
  payload += " ";
  payload += value_type;
  payload += "=";
  payload += value;
  client.publish(topic, (char*) payload.c_str());
  Serial.println(payload);
}

