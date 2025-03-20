#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

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
}

// Function to post data to the server
void postData() {
    if (WiFi.status() == WL_CONNECTED) {
        WiFiClient client;
        HTTPClient http;
        http.begin(client, "http://10.2.16.116:8004/cin/create/3");
        http.addHeader("Content-Type", "application/json");
        http.addHeader("Authorization", "Bearer 2dcd1f53e30be7479b1eaa1e15b1c292");
        
        DynamicJsonDocument jsonDoc(1024);  // Create a JSON document
        jsonDoc["param1"] = "temp";
        // jsonDoc["LCT"] = "humi";
        // jsonDoc["Vehicle Number"] = "v";
        String requestBody;  // Serialize JSON to a string
        serializeJson(jsonDoc, requestBody);

        int httpResponseCode = http.POST(requestBody);  // Send POST request
        if (httpResponseCode > 0) {
            String response = http.getString();
            Serial.println(httpResponseCode);
            Serial.println(response);
        } else {
            Serial.print("Error on sending POST: ");
            Serial.println(httpResponseCode);
        }
        http.end();  // End the HTTP connection
    } else {
        Serial.println("WiFi not connected. Cannot send data.");
    }
}

void loop() {
    postData();
    delay(3000); // Delay between POST requests
}
