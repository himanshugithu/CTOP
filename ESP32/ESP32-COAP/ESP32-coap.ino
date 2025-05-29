import network
import time
import ujson
from microcoapy import Coap
from microcoapy.coap_packet import CoapPacket
from machine import Pin

# WiFi Credentials
SSID = "myssid"
PASSWORD = "password"
led = Pin(2, Pin.OUT)

# CoAP Server Details
SERVER_IP = "10.2.16.116"   # Change to your actual CoAP server IP
SERVER_PORT = 5685          # Change to your actual server port
RESOURCE_PATH = "cin/create/73"  # Without leading slash is fine in microcoapy

# Connect to WiFi
def connect_wifi():
    wlan = network.WLAN(network.STA_IF)
    wlan.active(True)
    if not wlan.isconnected():
        print("📡 Connecting to WiFi...")
        wlan.connect(SSID, PASSWORD)
        while not wlan.isconnected():
            led.value(1)
            time.sleep(0.5)
            led.value(0)
            time.sleep(0.5)
    print("✅ Connected! IP Address:", wlan.ifconfig())
    led.value(1)

# Handle CoAP Response
def response_callback(packet: CoapPacket):
    print("📩 Response received:")
    print(f"🔹 Message ID: {packet.messageid}")
    try:
        payload_bytes = packet.payload
        # Directly decode the payload (no splitting needed)
        print(f"🔹 Decoded Message: {payload_bytes.decode('utf-8')}")
    except Exception as e:
        print(f"❌ Payload decode error: {e}")
    print(f"🔹 Response Code: {packet.code}")

# Send CoAP POST requests
def send_coap_series():
    coap_client = Coap()
    coap_client.response_callback = response_callback
    coap_client.start()

    count = 1
    try:
        while True:
            payload_dict = {
                "token": "f191ec7d1cef1326e1bccb6b6fc6e8f6",
                "test": str(count)
            }
            payload = ujson.dumps(payload_dict)

            print(f"🚀 Sending POST request {count} with payload: {payload}")
            message_id = coap_client.post(SERVER_IP, SERVER_PORT, RESOURCE_PATH, payload.encode('utf-8'))
            print(f"✅ Sent with Message ID: {message_id}")

            for _ in range(5):
                coap_client.poll(1000)  # Wait up to 5 seconds total

            count += 1
            time.sleep(5)  # Delay between sends

    except Exception as e:
        print("❌ Error occurred:", e)
    finally:
        coap_client.stop()
        led.value(0)
        print("🛑 CoAP client stopped.")

# Run the program
connect_wifi()
send_coap_series()
