#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include "ctop-http.h"
#include "ctop-mqtt.h"

const char* ssid = "myssid";
const char* password = "password";

void setup() {
    Serial.begin(115200);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }
    Serial.println("Connected to WiFi");
    client.setServer(mqtt_server, mqtt_port);
}


// Function to post data to the server

void loop() {
    client.loop();
    postData();
    delay(3000); // Delay between POST requests
    sendMQTTData();
    delay(3000);
}
