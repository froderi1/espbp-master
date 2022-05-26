/*
  On WEMOS D1 mini connect A0 via 180kOhm R to VCC

SETUP: pinMode(A0, INPUT);
  
*/

void b_voltage(){

  String payload;
  unsigned int raw=0;
  float volt=0.0;
  
  raw = analogRead(A0);
  volt=raw/1023.0;

  payload = "battery,device="; // influxDB Measurement,Tag
  payload += DEVICE_NAME;
  payload += " voltage=";
  payload += String(volt);
  client.publish(topic, (char*) payload.c_str());
  Serial.println(payload);

}
