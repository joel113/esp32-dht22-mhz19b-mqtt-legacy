
#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <SoftwareSerial.h>
#include "DHT.h"
#include "MHZ19.h"

#define DHTTYPE DHT22

#define RX_PIN 33
#define TX_PIN 32

const char* ssid = "";
const char* password = "";
char* wifiHostName = "";

const char* mqtt_server = "joel-telegraf";

WiFiClient espClient;

PubSubClient client(espClient);

const int DHTPin = 4;

DHT dht(DHTPin, DHTTYPE);

MHZ19 mhz19;

SoftwareSerial mySerial(RX_PIN, TX_PIN);

void setup() {
  Serial.begin(115200);
  dht.begin();
  mySerial.begin(9600);
  mhz19.printCommunication();
  mhz19.begin(mySerial);
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
  int co2 = mhz19.getCO2();

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
  }
  else if(mhz19.errorCode != RESULT_OK) {
    Serial.println("Failed to read from MHZ19 sensor due to error code."); 
  }
  else {
    StaticJsonDocument<200> jsonDocument;
    jsonDocument["temperature"] = t;
    jsonDocument["humidity"] = h;
    jsonDocument["co2"] = co2;
    
    serializeJson(jsonDocument, Serial);
  
    String json_value;
    serializeJson(jsonDocument, json_value);
  
    char mqtt_value[200];
    json_value.toCharArray(mqtt_value, 200);
    
    client.publish("/joel-sense-1/sensor", mqtt_value, true);
  }
}
