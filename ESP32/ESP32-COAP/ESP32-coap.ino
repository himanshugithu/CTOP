import network
import time
import ujson
from microcoapy import Coap
from microcoapy.coap_packet import CoapPacket
from machine import Pin

SSID = "myssid"
PASSWORD = "password"
led = Pin(22, Pin.OUT)

SERVER_IP = "10.2.16.116"
SERVER_PORT = 5685
RESOURCE_PATH = "/cin/create/68"

def connect_wifi():
    wlan = network.WLAN(network.STA_IF)
    wlan.active(True)
    if not wlan.isconnected():
        print("📡 Connecting to WiFi...")
        wlan.connect(SSID, PASSWORD)
        while not wlan.isconnected():
            time.sleep(1)
    print("✅ Connected! IP Address:", wlan.ifconfig()[0])
    led.value(1)

def response_callback(packet: CoapPacket):
    try:
        print("📩 Response received:")
        print(f"🔹 Message ID: {packet.messageid}")
        print(f"🔹 Payload: {packet.payload.decode()}")
    except Exception as e:
        print(f"❌ Payload decode error: {e}")

def send_coap_series():
    coap_client = Coap()
    coap_client.response_callback = response_callback
    coap_client.start()
    count = 1
    try:
        while True:
            data = {
                    "token": "Bearer  668aca94c18c7ece8878ad2581911993",
                    "Test4": "Test4",
                    "Test5": "Test5",
                    "Test6": "COAP Test"
                }
            json_payload = ujson.dumps(data)

            print(f"🚀 Sending POST request {count} with payload: {json_payload}")
            message_id = coap_client.post(SERVER_IP, SERVER_PORT, RESOURCE_PATH, json_payload.encode('utf-8'))
            print(f"✅ Sent with Message ID: {message_id}")

            for _ in range(5):
                coap_client.poll(1000)
            count += 1
            time.sleep(5)
    except Exception as e:
        print("❌ Error occurred:", e)
    finally:
        coap_client.stop()
        print("🛑 CoAP client stopped.")
        led.value(0)

connect_wifi()
send_coap_series()
