# EXP09 Part A: publish the actual digital IR output once per second.
from machine import Pin
import network
import time
from umqtt.simple import MQTTClient

# Enter the same network and broker used by MQTTX/the subscriber.
SSID = "YOUR_WIFI_SSID"
PASSWORD = "YOUR_WIFI_PASSWORD"
MQTT_BROKER = "YOUR_PC_LAN_IP"
MQTT_PORT = 1883
MQTT_CLIENT_ID = b"ESP32_IR_SENSOR"  # Must be unique among connected clients.
MQTT_TOPIC = b"sensor_data"
ir = Pin(27, Pin.IN)  # IR module digital OUT; check its active polarity.

wifi = network.WLAN(network.STA_IF)
wifi.active(True)
if not wifi.isconnected():
    print("Connecting to Wi-Fi...")
    wifi.connect(SSID, PASSWORD)
    while not wifi.isconnected():
        print("Waiting for Wi-Fi...")
        time.sleep(1)
print("Wi-Fi connected!")
print("ESP32 IP:", wifi.ifconfig()[0])

# The broker distributes each published message to matching subscribers.
print("Connecting to MQTT broker...")
client = MQTTClient(MQTT_CLIENT_ID, MQTT_BROKER, port=MQTT_PORT)
client.connect()
print("MQTT connected!")
print("Broker:", MQTT_BROKER)
print("Topic:", MQTT_TOPIC.decode())
print("--------------------------------")

while True:
    sensor_value = ir.value()
    print("IR Sensor Value:", sensor_value)
    client.publish(MQTT_TOPIC, str(sensor_value).encode())
    time.sleep(1)
