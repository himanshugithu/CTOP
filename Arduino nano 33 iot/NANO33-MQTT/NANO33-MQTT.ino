 #include <WiFiNINA.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>  // Include ArduinoJson library

// WiFi and MQTT broker details
const char* ssid = "myssid";
const char* password = "password";
const char* mqtt_server = "10.2.16.116";  // MQTT broker IP
const int mqtt_port = 1884;               // MQTT broker port

// MQTT topic
const char* topic = "oneM2M/req/WM15-0000-0001";  // MQTT topic to publish to

WiFiClient espClient;
PubSubClient client(espClient);

unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE (256)  // Buffer size for MQTT message
char msg[MSG_BUFFER_SIZE];

int pm25_value = 1;  // Start value

void setup() {
  Serial.begin(115200);
  
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("WiFi module not found!");
    while (true);
  }

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected!");

  client.setServer(mqtt_server, mqtt_port);
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    String clientId = "Nano33Client-";
    clientId += String(random(0xffff), HEX);

    if (client.connect(clientId.c_str())) {  // No authentication
      Serial.println("Connected to MQTT Broker");
    } else {
      Serial.print("Failed, rc=");
      Serial.print(client.state());
      Serial.println(" Trying again in 5 seconds...");
      delay(5000);
    }
  }
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  unsigned long now = millis();
  if (now - lastMsg > 10000) {  // Publish every 10 seconds
    StaticJsonDocument<256> doc;  // JSON document size

    // Construct JSON payload
    doc["Authentication"] = "Bearer 1e7e84f7445182e624376f3b0913d0e3";
    doc["token_id"] = "19";

    JsonObject data = doc.createNestedObject("data");
    data["BinData"] = String(pm25_value);  // Send as a string
    data["LCT"] = "25.6";
    data["Vehicle Number"] = "60";

    // Serialize JSON to a char array
    serializeJson(doc, msg, MSG_BUFFER_SIZE);
    Serial.print("Publishing message: ");
    Serial.println(msg);
    client.publish(topic, msg);
    pm25_value++;  // Increment the pm2.5 value
    lastMsg = now;
  }
}
