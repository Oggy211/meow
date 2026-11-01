# INCOMPLETE: only lines 1-23 are visible in the supplied screenshot.
# This fragment connects to Wi-Fi; the sensor/upload loop is not available.
# Wi-Fi and API credentials were replaced with local configuration placeholders.
import dht
from machine import Pin
import network
import time
import requests

SSID = "YOUR_WIFI_SSID"
PASSWORD = "YOUR_WIFI_PASSWORD"
API_KEY = "YOUR_THINGSPEAK_WRITE_KEY"

sensor = dht.DHT11(Pin(14))  # DHT11 data signal from GPIO14.
wlan = network.WLAN(network.STA_IF)
wlan.active(False)
time.sleep(1)
wlan.active(True)
time.sleep(1)
print("Connecting to Wi-Fi...")
wlan.connect(SSID, PASSWORD)
# Screenshot ends here. Full exp7.py is required to recover the upload logic.
