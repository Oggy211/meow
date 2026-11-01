# EXP08 ESP32 LED control using HTTP and WebSocket

## Aim

Control an external ESP32 LED from a browser using two methods: HTTP requests and a persistent WebSocket connection.

## Part status

Both documented ESP32 parts are present: HTTP in access-point mode and WebSocket in station mode. Run one program at a time.

## Files

- [Components and connections](components_and_connections.md)
- [Viva questions and answers](viva_questions_and_answers.md)

## Part A HTTP server in access point mode

### Code

- [part_a_http_led.py](code/part_a_http_led.py)

### Setup

1. Use a classic ESP32 development board with MicroPython firmware and a USB data cable. GPIO numbers are chip GPIO numbers, not physical header positions.
2. Open the file in Thonny with the MicroPython ESP32 interpreter selected; save the chosen program on the device as main.py or run it interactively. Run one program at a time on each board.
3. Choose an access-point password at least 8 characters long in the code.
4. Start the program, connect the phone/PC to ESP32-WebServer, and open the HTTP address printed by the ESP32. Keep the local Wi-Fi connection even if the phone reports no internet.

### Expected behavior

The ESP32 hosts its own Wi-Fi network. Browser GET requests for /?led=on and /?led=off drive GPIO2 high and low; the returned HTML page displays the current LED state.

### Notes

- An onboard LED on GPIO2 is board dependent; use the external circuit for predictable behavior.
- An embedded source screenshot says GPIO26, while the report program uses GPIO2. This guide follows the program.
- The server is a local unencrypted lab demonstration with one request handled at a time.

## Part B WebSocket server in station mode

### Code

- [part_b_websocket_led.py](code/part_b_websocket_led.py)

### Setup

1. Use a classic ESP32 development board with MicroPython firmware and a USB data cable. GPIO numbers are chip GPIO numbers, not physical header positions.
2. Open the file in Thonny with the MicroPython ESP32 interpreter selected; save the chosen program on the device as main.py or run it interactively. Run one program at a time on each board.
3. Enter Wi-Fi SSID and password; the original classroom credentials are replaced with placeholders.
4. Move the external LED control lead to GPIO25. Connect the browser to the same LAN, then visit the ESP32 IP printed in the shell.
5. Wait for WebSocket Connected before using the buttons. Browser JavaScript sends ON and OFF strings over ws:// to port 80.

### Expected behavior

An HTTP page opens a persistent WebSocket connection. ON and OFF messages set GPIO25 and return LED is ON or LED is OFF status text without reloading the page.

### Notes

- The supplied WebSocket implementation handles one connected browser at a time.
- This is source-preserving lab code, not a complete RFC implementation: fragmented frames, arbitrary binary traffic and full close handling are unsupported; ping handling does not echo the payload; request reads assume the headers arrive in one receive call.
- Source socket.send calls can send fewer bytes than requested; this implementation has no full-send retry. It was not exercised on hardware here.
- On normal disconnect, the source does not explicitly close the client socket; repeated reconnects can depend on eventual resource cleanup.

## Missing information

- No complete code is missing for either documented part. Exact LED resistor value is not legible, so 220 to 330 ohms is identified as a recommendation.

## Source changes

- Separated the two complete report programs into independent Python files.
- Preserved GPIO2 for HTTP and GPIO25 for WebSocket.
- Replaced classroom Wi-Fi credentials and AP password with configurable placeholders.
- No complete WebSocket protocol rewrite was made; source limitations are explicit.

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
