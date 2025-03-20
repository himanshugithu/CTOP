#ifndef MQTT_SEND_H
#define MQTT_SEND_H

#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

const char* mqtt_server = "10.2.16.116";
const int mqtt_port = 1884;
const char* topic = "oneM2M/req/WM15-0000-0001";

WiFiClient espClient;
PubSubClient client(espClient);
int count1 = 0;

void connectMQTT() {
    while (!client.connected()) {
        Serial.print("Attempting MQTT connection...");
        String clientId = "ESP32Client-" + String(random(0xffff), HEX);
        if (client.connect(clientId.c_str())) {
            Serial.println("Connected to MQTT Broker");
        } else {
            Serial.print("Failed, rc=");
            Serial.print(client.state());
            Serial.println(" Trying again in 5 seconds...");
            delay(5000);
        }
    }
}

void sendMQTTData() {
    if (!client.connected()) {
        connectMQTT();
    }
    Serial.println("Sending data using MQTT");
    StaticJsonDocument<256> doc;
    doc["Authentication"] = "Bearer 1e7e84f7445182e624376f3b0913d0e3";
    doc["token_id"] = "19";

    JsonObject data = doc.createNestedObject("data");
    data["BinData"] = String(count1);
    data["LCT"] = String(count1 + 5);
    data["Vehicle Number"] = "MQTT";
    count1++;

    char msg[256];
    serializeJson(doc, msg, sizeof(msg));

    Serial.print("Publishing message: ");
    Serial.println(msg);

    if (client.publish(topic, msg)) {
        Serial.println("Message published successfully!");
    } else {
        Serial.println("Message failed to publish!");
    }
}

#endif // MQTT_SEND_H
