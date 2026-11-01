# EXP08 Components and connections

Both documented ESP32 parts are present: HTTP in access-point mode and WebSocket in station mode. Run one program at a time.

## Part A HTTP server in access point mode

### Components

| Component | Quantity | Details |
| --- | --- | --- |
| ESP32 development board | 1 | Classic ESP32 pin numbering; the photos show an ESP32 development board. |
| LED | 1 | External LED is shown in the photographs. |
| Series resistor | 1 | Use 220 to 330 ohms as a practical recommendation; exact photographed value is unreadable. |
| Breadboard and jumper leads | 1 set |  |
| USB data cable and computer with Thonny | 1 each |  |
| Phone or PC with a web browser | 1 |  |

### Connections

| From | To | Details |
| --- | --- | --- |
| ESP32 GPIO2 | 220 to 330 ohm resistor | Source code selects GPIO2. |
| Resistor other end | LED anode positive longer leg |  |
| LED cathode negative shorter leg | ESP32 GND |  |
| ESP32 USB | PC USB | Power and programming. Phone connects wirelessly to ESP32-WebServer. |

### Notes

- An onboard LED on GPIO2 is board dependent; use the external circuit for predictable behavior.
- An embedded source screenshot says GPIO26, while the report program uses GPIO2. This guide follows the program.
- The server is a local unencrypted lab demonstration with one request handled at a time.

## Part B WebSocket server in station mode

### Components

| Component | Quantity | Details |
| --- | --- | --- |
| ESP32 development board | 1 | Classic ESP32 pin numbering; the photos show an ESP32 development board. |
| LED | 1 | External LED is shown in the photographs. |
| Series resistor | 1 | Use 220 to 330 ohms as a practical recommendation; exact photographed value is unreadable. |
| Breadboard and jumper leads | 1 set |  |
| USB data cable and computer with Thonny | 1 each |  |
| Phone or PC with a web browser | 1 |  |
| Wi-Fi access point or router | 1 | Board and browser must be on the same reachable LAN; a router with client isolation can block access. |

### Connections

| From | To | Details |
| --- | --- | --- |
| ESP32 GPIO25 | 220 to 330 ohm resistor | The WebSocket code uses GPIO25, not the HTTP part GPIO2. |
| Resistor other end | LED anode |  |
| LED cathode | ESP32 GND |  |
| ESP32 USB | PC USB |  |

### Notes

- The supplied WebSocket implementation handles one connected browser at a time.
- This is source-preserving lab code, not a complete RFC implementation: fragmented frames, arbitrary binary traffic and full close handling are unsupported; ping handling does not echo the payload; request reads assume the headers arrive in one receive call.
- Source socket.send calls can send fewer bytes than requested; this implementation has no full-send retry. It was not exercised on hardware here.
- On normal disconnect, the source does not explicitly close the client socket; repeated reconnects can depend on eventual resource cleanup.

See the [experiment README](README.md) for setup, expected behavior and missing items.

## Sources

Archive paths below refer to the supplied IoT ZIP. User contributions are identified separately.

- IOT/EXP8/EXP8_2024300174_IOT.docx
- IOT/EXP8/EXP8_2024300174_IOT.pdf
- IOT/EXP8 hardware photos and browser and terminal screenshots

### Technical references

- [MicroPython ESP32 quick reference](https://www.micropython.org/resources/docs/en/latest/esp32/quickref.html)
- [MicroPython low level Bluetooth](https://docs.micropython.org/en/latest/library/bluetooth.html)
- [MicroPython umqtt simple README](https://github.com/micropython/micropython-lib/blob/master/micropython/umqtt.simple/README.rst)
- [Mosquitto authentication methods](https://mosquitto.org/documentation/authentication-methods/)
- [Mosquitto configuration reference](https://mosquitto.org/man/mosquitto-conf-5.html)
