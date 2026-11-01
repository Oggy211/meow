# EXP09 Part B: the original report's ultrasonic-topic subscriber.
# This is NOT paired with the IR publisher: the source topic differs.
import network
import time
from umqtt.simple import MQTTClient

SSID = "YOUR_WIFI_SSID"
PASSWORD = "YOUR_WIFI_PASSWORD"
MQTT_BROKER = "YOUR_PC_LAN_IP"  # Source used another broker IP than the publisher.
MQTT_PORT = 1883
MQTT_CLIENT_ID = b"ESP32_SUBSCRIBER_01"
MQTT_TOPIC = b"anshul/ultrasonic"  # Preserved source topic.

wifi = network.WLAN(network.STA_IF)
wifi.active(True)
if not wifi.isconnected():
    print("Connecting to Wi-Fi...")
    wifi.connect(SSID, PASSWORD)
    while not wifi.isconnected():
        print("Waiting for Wi-Fi...")
        time.sleep(1)
print()
print("Wi-Fi connected!")
print("ESP32 IP:", wifi.ifconfig()[0])

# A callback handles a message delivered on the subscribed topic.
def received_message(topic, message):
    print("Topic:", topic.decode())
    print("Ultrasonic Sensor Value:", message.decode())
    print("-----------------------------")

print()
print("Connecting to MQTT broker...")
client = MQTTClient(MQTT_CLIENT_ID, MQTT_BROKER, port=MQTT_PORT)
client.set_callback(received_message)
client.connect()
print("MQTT connected!")
print("Broker:", MQTT_BROKER)
client.subscribe(MQTT_TOPIC)
print("Subscribed to:", MQTT_TOPIC.decode())
print()
print("Waiting for ultrasonic sensor data...")
print("--------------------------------------")

while True:
    client.check_msg()  # Poll for new messages without waiting indefinitely.
    time.sleep(0.1)
