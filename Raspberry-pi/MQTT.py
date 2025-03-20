import paho.mqtt.client as mqtt
import json
import time

# MQTT broker details
MQTT_BROKER = "10.2.16.116"
MQTT_PORT = 1884
MQTT_TOPIC = "oneM2M/req/WM15-0000-0001"

# Callback when the client connects to the broker
def on_connect(client, userdata, flags, rc):
    if rc == 0:
        print("Connected to MQTT Broker!")
    else:
        print(f"Failed to connect, return code {rc}")

# Create MQTT client
client = mqtt.Client()
client.on_connect = on_connect

# Connect to the broker
client.connect(MQTT_BROKER, MQTT_PORT, 60)
client.loop_start()

# Send data every 10 seconds
pm25_value = 1
while True:
    payload = {
        "Authentication": "Bearer 1e7e84f7445182e624376f3b0913d0e3",
        "token_id": "19",
        "data": {
            "BinData": str(pm25_value),
            "LCT": "25.6",
            "Vehicle Number": "MQTT"
        }
    }

    msg = json.dumps(payload)
    print(f"Publishing message: {msg}")
    client.publish(MQTT_TOPIC, msg)

    pm25_value += 1  # Increment value
    time.sleep(10)  # Wait 10 seconds
