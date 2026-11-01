# EXP07 DHT11 monitoring and upload to ThingSpeak

Read temperature and relative humidity on an ESP32 and upload both readings to ThingSpeak.

## Files

- [Complete exp7.py](code/ESP32/exp7.py)
- [Components and connections](components_and_connections.md)
- [Viva questions and answers](viva_questions_and_answers.md)
- [Recovered original fragment](code/ESP32/recovered_fragment_INCOMPLETE.py)

## What was completed

The screenshots show DHT11 on GPIO14, Wi-Fi initialization, serial measurements and ThingSpeak charts. The full upload loop is not visible. The complete `exp7.py` keeps the documented pin and field mapping and adds the off-screen logic at the user's request. It is a completed implementation, not a verbatim recovery of hidden lines. Keep the original fragment as a source reference; run `exp7.py`.

## Setup

1. Connect the DHT11 module DATA to GPIO14, GND to GND and VCC to a compatible 3.3 V supply as described in the connection file.
2. Flash suitable ESP32 MicroPython firmware and select the MicroPython ESP32 interpreter in Thonny.
3. Install the MicroPython `requests` package with JSON and timeout support on the ESP32. In an internet-connected MicroPython REPL, `import mip; mip.install("requests")` installs it. Installing desktop Python requests alone does not install it on the board.
4. In ThingSpeak, enable Field 1 for temperature and Field 2 for humidity. Obtain this channel's **Write API key**.
5. Replace `SSID`, `PASSWORD` and `API_KEY` placeholders at the top of `exp7.py`. The screenshot credentials are not included.
6. Run the file in Thonny. For automatic startup, save this complete program on the ESP32 as `main.py`; run one experiment at a time.
7. Open your ThingSpeak channel's private view and check that both charts receive new entries.

## Program behavior

- Waits up to 20 seconds for Wi-Fi and prints the IP after connection.
- Calls `sensor.measure()`, then reads temperature in C and humidity in percent.
- Sends one HTTPS JSON POST to the ThingSpeak update endpoint: Field 1 temperature, Field 2 humidity.
- Treats only HTTP 200 plus a positive integer entry ID as an accepted upload. A body of `0` means rejection.
- Closes each response, handles sensor/network errors and waits 20 seconds between attempts.
- Reconnects Wi-Fi if the board is disconnected. Stop from Thonny with Ctrl+C.

The 20-second wait is an added setting. It exceeds the documented 15-second minimum update interval for a free ThingSpeak channel. The screenshot's `ECONNABORTED` message is an intermittent network error; successful sensor readings alone do not prove an upload succeeded.

## Checks and limits

The program's API response handling, response cleanup, Wi-Fi timeout and retry behavior are checked using simulated device/network responses. Physical DHT11 readings, ESP32 TLS/network compatibility and live channel updates still need a board test. Use the current MicroPython requests package; older libraries without the `timeout` argument are not suitable for this file.

This experiment has one documented ESP32 implementation; it has no separate STM32 program in the supplied material.

## Source record

- Original lab reports and screenshots in `IOT/EXP7/`, plus the misplaced report in `IOT/EXP1/`.
- Additional ThingSpeak chart screenshot and `Screenshot 2026-11-01 161546.png` supplied in chat on 1 November 2026.
- The off-screen upload loop, bounded connection wait and error handling were added on 1 November 2026. No exact reconstruction of hidden lines is claimed.

## Technical references

- [ThingSpeak Write Data API](https://www.mathworks.com/help/thingspeak/writedata.html)
- [ThingSpeak channel update limits](https://www.mathworks.com/help/thingspeak/channel-control.html)
- [MicroPython DHT interface](https://docs.micropython.org/en/latest/esp8266/tutorial/dht.html)
- [MicroPython requests implementation](https://github.com/micropython/micropython-lib/tree/master/python-ecosys/requests)

[Back to repository](../../README.md)
