"""EXP07: ESP32 DHT11 readings uploaded to ThingSpeak.

GPIO14 and the two channel fields follow the supplied screenshots/report.
The off-screen Wi-Fi wait and upload loop were completed on 1 November 2026.
Use MicroPython on ESP32, not desktop Python. Save as main.py to run at boot.
"""

import dht
from machine import Pin
import network
import time
import requests

# Replace these three placeholders with your own settings before running.
SSID = "YOUR_WIFI_SSID"
PASSWORD = "YOUR_WIFI_PASSWORD"
API_KEY = "YOUR_THINGSPEAK_WRITE_KEY"

API_URL = "https://api.thingspeak.com/update"
UPLOAD_INTERVAL = 20  # Seconds between attempts; allow for cloud rate limits.
WIFI_TIMEOUT = 20
HTTP_TIMEOUT = 10

sensor = dht.DHT11(Pin(14))  # DATA wire connects to ESP32 GPIO14.
wlan = network.WLAN(network.STA_IF)


def connect_wifi():
    """Connect or reconnect, without waiting forever for a failed network."""
    if wlan.isconnected():
        return

    wlan.active(True)
    print("Connecting to Wi-Fi...")
    wlan.connect(SSID, PASSWORD)
    started = time.ticks_ms()
    while not wlan.isconnected():
        if time.ticks_diff(time.ticks_ms(), started) >= WIFI_TIMEOUT * 1000:
            wlan.disconnect()
            raise OSError("Wi-Fi timed out; check credentials and signal")
        time.sleep(0.5)

    print("Wi-Fi connected")
    print("IP address:", wlan.ifconfig()[0])


def upload_reading(temperature, humidity):
    """Return True only when ThingSpeak returns a positive entry ID."""
    response = None
    try:
        # Field 1 is temperature in C; Field 2 is relative humidity in percent.
        response = requests.post(
            API_URL,
            json={"api_key": API_KEY, "field1": temperature, "field2": humidity},
            timeout=HTTP_TIMEOUT,
        )
        result = response.text.strip()
        print("ThingSpeak response:", result)

        # HTTP 200 with a body of 0 still means that the update failed.
        if response.status_code == 200 and result.isdigit() and int(result) > 0:
            print("Upload accepted; entry ID:", result)
            return True

        print("Upload rejected; HTTP", response.status_code,
              "- check the Write API key and update interval")
        return False
    finally:
        if response is not None:
            response.close()  # Release the socket after success or failure.


def main():
    if any(not value or value.startswith("YOUR_")
           for value in (SSID, PASSWORD, API_KEY)):
        raise ValueError("Set SSID, PASSWORD and API_KEY at the top of exp7.py")

    time.sleep(2)  # Give the DHT11 time to settle after power-up.
    try:
        while True:
            try:
                connect_wifi()
                sensor.measure()  # Take one fresh temperature/humidity sample.
                temperature = sensor.temperature()
                humidity = sensor.humidity()
                print("Temperature:", temperature, "C")
                print("Humidity:", humidity, "%")
                print("Sending data to ThingSpeak...")
                upload_reading(temperature, humidity)
            except (OSError, ValueError) as error:
                print("Error:", error)  # Retry next cycle after a sensor/network error.

            print("------------------------------")
            time.sleep(UPLOAD_INTERVAL)
    except KeyboardInterrupt:
        print("Experiment 7 stopped")


if __name__ == "__main__":
    main()
