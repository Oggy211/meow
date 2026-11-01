# EXP08 Viva questions and answers

14 short questions covering the documented experiment.

## 1 What does the ESP32 do in this experiment?

It hosts a web interface and changes a GPIO output when a browser sends an LED command.

## 2 What is the difference between AP and STA modes?

AP mode creates a Wi-Fi network. STA mode joins an existing Wi-Fi network.

## 3 Which pins do the two parts use?

HTTP uses GPIO2; WebSocket uses GPIO25. Rewire the LED when changing parts.

## 4 What is HTTP?

A request-response application protocol. The browser requests a resource and the server returns a response.

## 5 How is an LED command represented in the HTTP part?

As a GET request for /?led=on or /?led=off.

## 6 Why does the server bind to 0.0.0.0 port 80?

0.0.0.0 listens on the available local interfaces, and 80 is the conventional HTTP port.

## 7 How does WebSocket differ from the HTTP button method?

After an HTTP upgrade handshake, it keeps a bidirectional connection open so messages can flow without a full page refresh.

## 8 What does status code 101 mean?

Switching Protocols; the server accepts the upgrade from HTTP to WebSocket.

## 9 Why is a series resistor used with an LED?

It limits current through the LED and GPIO output.

## 10 What is a socket?

A programming interface for sending and receiving network data between endpoints.

## 11 Why can a browser fail to connect although Wi-Fi is connected?

The IP may be wrong, the program may not be running, the browser may be on another LAN, or client isolation may block device-to-device traffic.

## 12 What is the role of the Sec-WebSocket-Accept field?

It is derived from the client key and a protocol GUID to complete the WebSocket handshake.

## 13 Does this experiment require internet access?

No. Local connectivity between the browser and ESP32 is enough.

## 14 Can this code directly switch a mains appliance?

No. GPIO only provides a low-voltage control signal; an appropriate rated interface is required for an appliance.

See the [experiment README](README.md) for the available code and its limitations.

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
