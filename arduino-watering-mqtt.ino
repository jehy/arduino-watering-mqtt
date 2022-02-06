#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <PubSubClient.h>

#include "WiFiUtils.h"
#include "settings.h"
WiFiClient client;
PubSubClient mqttClient(client);

int fromLastWatering = 0;

void setup()
{

  Serial.begin(115200);
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite (RELAY_PIN, RELAY_OFF);
  WiFi.mode(WIFI_STA); //be only wifi client, not station
  WiFiUtils::printNetworks();
  WiFi.hostname("Water_Sensor_1");
}

void finish() {
  WiFi.disconnect(1);
  delay(LOOP_ITERATION);
  fromLastWatering += LOOP_ITERATION;
}

void mqqtConnect() {

  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.printf("Attempting to connect to WPA SSID %s\n", WIFI_SSID);
    delay(1200);
  }

  WiFiUtils::printCurrentNet();
  WiFiUtils::printWifiData();


  while (!mqttClient.connected()) {
    if (mqttClient.connect("ArduinoClient")) {
      Serial.println("MQTT reconnected");
      return;
    } else {
      Serial.print("MQTT failed, rc=");
      Serial.print(mqttClient.state());
      delay(1000);
    }
  }
}

void loop() {

  bool res = false;
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  int humidityValue = analogRead(SENSOR_PIN);
  Serial.printf("ground humidity: %d", humidityValue);
  char dataString[5];       // number of digits + 1 for null terminator
  itoa(humidityValue, dataString, 10);  // int value, pointer to string, base number
  mqqtConnect();
  mqttClient.loop();
  res = mqttClient.publish(WATER_STATUS_TOPIC, dataString);
  mqttClient.loop();
  Serial.printf("himidity publish: %d\n");
  Serial.println("MQTT request sent");

  if (humidityValue < DRYNESS_NEED_WATER) {
    Serial.println("All ok. Waiting.");
    finish();
    return;
  }
  if (fromLastWatering != 0 && fromLastWatering < MIN_WATERING_INTERVAL) {
    Serial.println("Need watering but interval too short. Waiting.");
    finish();
    return;
  }
  Serial.println("Need watering. Writing high");
  mqttClient.loop();
  res = mqttClient.publish(WATER_STATE_TOPIC, "1");
  mqttClient.loop();
  Serial.printf("status publish on: %d\n");
  digitalWrite (RELAY_PIN, LOW);
  delay(PUMP_WORK_TIME);
  Serial.println("Disabling pump, Writing low");
  digitalWrite (RELAY_PIN, RELAY_OFF);
  delay(1000);
  mqttClient.loop();
  mqqtConnect();
  mqttClient.loop();
  res = mqttClient.publish(WATER_STATE_TOPIC, "0");
  mqttClient.loop();
  Serial.printf("status publish off: %d\n");
  fromLastWatering = 0;
  Serial.println("Watering completed.");
  finish();
}
