#include <WiFiNINA.h>
#include <ArduinoHttpClient.h>
#include <ArduinoJson.h>

const char* ssid = "myssid";
const char* password = "password";
const char* serverAddress = "10.2.16.116";  // Server IP
const int port = 8004;                      // Server port
// const int port = 443; 

// Secure Connection (SSL/TLS) : HTTPS 
WiFiSSLClient wifiClient;   // Use WiFiSSLClient for HTTPS
HttpClient httpClient(wifiClient, serverAddress, port);

// Uncomment below for non-secure connection (HTTP)
// WiFiClient wifiClient;     
// HttpClient httpClient(wifiClient, serverAddress, port);

void setup() {
    Serial.begin(115200);

    if (WiFi.status() == WL_NO_MODULE) {
        Serial.println("WiFi module not found!");
        while (true);  // Halt execution
    }

    Serial.print("Connecting to WiFi");
    WiFi.begin(ssid, password);
    
    int retries = 0;
    while (WiFi.status() != WL_CONNECTED && retries < 20) {
        delay(1000);
        Serial.print(".");
        retries++;
    }

    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("\nConnected to WiFi");
    } else {
        Serial.println("\nFailed to connect to WiFi. Check credentials!");
        while (true);
    }
}

// Function to post data to the server
void postData() {
    if (WiFi.status() == WL_CONNECTED) {
        String url = "/cin/create/3";
        httpClient.beginRequest();
        httpClient.post(url);
        httpClient.sendHeader("Content-Type", "application/json");
        httpClient.sendHeader("Authorization", "Bearer 2dcd1f53e30be7479b1eaa1e15b1c292");

        // Create JSON document
        DynamicJsonDocument jsonDoc(1024);
        jsonDoc["param1"] = "temp";
        // jsonDoc["LCT"] = "humi";
        // jsonDoc["Vehicle Number"] = "v";

        String requestBody;
        serializeJson(jsonDoc, requestBody);

        httpClient.sendHeader("Content-Length", requestBody.length());
        httpClient.beginBody();
        httpClient.print(requestBody);
        httpClient.endRequest();

        int statusCode = httpClient.responseStatusCode();
        String response = httpClient.responseBody();

        Serial.print("HTTP Response code: ");
        Serial.println(statusCode);
        Serial.println(response);
    } else {
        Serial.println("WiFi not connected. Cannot send data.");
    }
}

void loop() {
    postData();
    delay(5000); // Send request every 5 seconds
}
