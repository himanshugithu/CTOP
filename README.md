# CTOP Project

This repository contains code for various IoT devices to send data to a server using HTTP and MQTT protocols. The project supports multiple hardware platforms, including Arduino Nano 33 IoT, ESP32, ESP8266, and Raspberry Pi.

---

## 📂 Directory Structure
```
CTOP/
├── Arduino_Nano_33_IoT/
│   ├── NANO33-HTTP/
│   │   └── NANO33-HTTP.ino
│   ├── NANO33-MQTT/
│   │   └── NANO33-MQTT.ino
│
├── ESP32/
│   ├── ESP32-HTTP/
│   │   └── ESP32-HTTP.ino
│   ├── ESP32-MQTT/
│   │   └── ESP32-MQTT.ino
│   ├── HTTP-MQTT/
│   │   ├── ctop-http.h
│   │   ├── ctop-mqtt.h
│   │   └── HTTP-MQTT.ino
│
├── ESP8266/
│   ├── 8266-HTTP/
│   │   └── 8266-HTTP.ino
│   ├── 8266-MQTT/
│   │   └── 8266-MQTT.ino
│
├── Raspberry_Pi/
│   ├── HTTP.py
│   ├── MQTT.py
│   ├── requirements.txt
│
└── README.md
```

---

## 🖥️ Supported Platforms

### Arduino Nano 33 IoT
- **NANO33-HTTP**: Sends data to a server using HTTP.
- **NANO33-MQTT**: Publishes data to an MQTT broker.

### ESP32
- **ESP32-HTTP**: Sends data to a server using HTTP.
- **ESP32-MQTT**: Publishes data to an MQTT broker.
- **HTTP-MQTT**: Combines HTTP and MQTT functionality.

### ESP8266
- **8266-HTTP**: Sends data to a server using HTTP.
- **8266-MQTT**: Publishes data to an MQTT broker.

### Raspberry Pi
- **HTTP.py**: Sends data to a server using HTTP.
- **MQTT.py**: Publishes data to an MQTT broker.
- **requirements.txt**: Lists Python dependencies.

---

## 🌟 Features
- **HTTP Communication**: Uses REST APIs to send data to a server.
- **MQTT Communication**: Publishes data to an MQTT broker.
- **JSON Payloads**: Data is serialized into JSON format for both HTTP and MQTT.

---

## ⚙️ Setup Instructions

### 📌 Arduino Devices
1. Install the required libraries in the Arduino IDE:
   - `WiFiNINA`
   - `ArduinoHttpClient`
   - `PubSubClient`
   - `ArduinoJson`
2. Open the respective `.ino` file for your device.
3. Update the WiFi credentials (`ssid` and `password`) and server details.
4. Upload the code to your device.

### 📌 ESP32 and ESP8266
1. Install the required libraries in the Arduino IDE:
   - `WiFi` for ESP32
   - `ESP8266WiFi.h` for ESP8266
   - `HTTPClient`
   - `PubSubClient`
   - `ArduinoJson`
2. Open the respective `.ino` file for your device.
3. Update the WiFi credentials (`ssid` and `password`) and server details.
4. Upload the code to your device.

### 📌 Raspberry Pi
1. Install Python dependencies:
   ```bash
   pip install -r requirements.txt
   ```
2. Run the desired script:
   - **For HTTP:**
     ```bash
     python Raspberry_Pi/HTTP.py
     ```
   - **For MQTT:**
     ```bash
     python Raspberry_Pi/MQTT.py
     ```

---

## 📜 License
This project is licensed under the MIT License. See the `LICENSE` file for details.

---

## 👤 Author
Developed by **Himanshu Fanibhare**.

---
---

📌 *Feel free to contribute or raise an issue if you encounter any problems!* 🚀

