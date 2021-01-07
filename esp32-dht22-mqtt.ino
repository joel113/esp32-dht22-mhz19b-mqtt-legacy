
#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include "DHT.h"

#define DHTTYPE DHT22

const char* ssid = "";
const char* password = "";
char* wifiHostName = "";

const char* mqtt_server = "";

WiFiClient espClient;
PubSubClient client(espClient);

const int DHTPin = 4;
DHT dht(DHTPin, DHTTYPE);

void setup() {
  Serial.begin(115200);
  dht.begin();
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  client.setServer(mqtt_server, 1883);
  delay(10000);
  Serial.println(WiFi.localIP());
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("joel-sense-1")) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void loop() {
  
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  delay(5000);

  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
  }
  else {
    StaticJsonDocument<200> jsonDocument;
    jsonDocument["temperature"] = t;
    jsonDocument["humidity"] = h;
    
    serializeJson(jsonDocument, Serial);
  
    String json_value;
    serializeJson(jsonDocument, json_value);
  
    char mqtt_value[200];
    json_value.toCharArray(mqtt_value, 200);
    
    client.publish("/joel-sense-2/sensor", mqtt_value, true);
  }
}
