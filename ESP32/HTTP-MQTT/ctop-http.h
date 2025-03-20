#ifndef CTOP_SEND_H
#define CTOP_SEND_H
         
#include <ArduinoJson.h>  
#include <HTTPClient.h>

int count = 0;

void postData() {
    if (WiFi.status() == WL_CONNECTED) {
        HTTPClient http;
        http.begin("http://10.2.16.116:8610/cin/create/19");
        http.addHeader("Content-Type", "application/json");
        http.addHeader("Authorization", "Bearer 1e7e84f7445182e624376f3b0913d0e3");
        
        DynamicJsonDocument jsonDoc(1024);// Create a JSON document
        jsonDoc["BinData"] = String(count);
        jsonDoc["LCT"] = String(count + 5);
        jsonDoc["Vehicle Number"] = "HTTP";
        count++;
        String requestBody;  // Serialize JSON to a string
        serializeJson(jsonDoc, requestBody);
        Serial.println("Sending data using HTTP");
        int httpResponseCode = http.POST(requestBody);  // Send POST request
          if (httpResponseCode > 0) 
          {
              String response = http.getString();
              Serial.println(httpResponseCode);
              Serial.println(response);
          } 
          else 
          {
              Serial.print("Error on sending POST: ");
              Serial.println(httpResponseCode);
          }
          http.end();  // End the HTTP connection
    } 
    else 
    {
        Serial.println("WiFi not connected. Cannot send data.");
    }
}

#endif // CTOP_SEND_H
