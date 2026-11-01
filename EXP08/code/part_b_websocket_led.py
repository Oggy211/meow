# EXP08 Part B: WebSocket LED control in station mode.
# Save only this program as main.py on the ESP32. External LED is on GPIO25.
# Single-client lab implementation; protocol limitations are listed in the guide.
import network
import socket
import time
import hashlib
import ubinascii
from machine import Pin
# WIFI
SSID = "YOUR_WIFI_SSID"
PASSWORD = "YOUR_WIFI_PASSWORD"
wifi = network.WLAN(network.STA_IF)
wifi.active(False)
time.sleep(1)
wifi.active(True)
time.sleep(1)
print("Connecting to Wi-Fi...")
wifi.connect(SSID, PASSWORD)
while not wifi.isconnected():
    print("Waiting for Wi-Fi...")
    time.sleep(1)
ip = wifi.ifconfig()[0]
print()
print("==============================")
print("ESP32 WEBSOCKET SERVER")
print("==============================")
print("Wi-Fi     :", SSID)
print("IP Address:", ip)
print("==============================")
# LED
led = Pin(25, Pin.OUT)
led.off()
state = "OFF"
# WEB PAGE
html = """<!DOCTYPE html>
<html>
<head>
<title>ESP32 WebSocket LED</title>
<style>
body {
    font-family: Arial;
    text-align: center;
    margin-top: 80px;
}
button {
    font-size: 25px;
    padding: 15px 40px;
    margin: 15px;
}
</style>
</head>
<body>
<h1>ESP32 WebSocket LED Control</h1>
<p id="status">Connecting...</p>
<button onclick="sendON()">
LED ON
</button>
<button onclick="sendOFF()">
LED OFF
</button>
<script>
var socket = new WebSocket(
    "ws://" + window.location.host
);
socket.onopen = function()
{
    document.getElementById("status").innerHTML =
    "WebSocket Connected";
};
socket.onmessage = function(event)
{
    document.getElementById("status").innerHTML =
    "ESP32: " + event.data;
};
socket.onclose = function()
{
    document.getElementById("status").innerHTML =
    "WebSocket Disconnected";
};
function sendON()
{
    socket.send("ON");
}
function sendOFF()
{
    socket.send("OFF");
}
</script>
</body>
</html>
"""
# RECEIVE EXACT NUMBER OF BYTES
def recv_exact(client, number):
    data = b""
    while len(data) < number:
        part = client.recv(number - len(data))
        if not part:
            return None
        data += part
    return data
# WEBSOCKET HANDSHAKE
def websocket_handshake(client, request):
    request_text = request.decode()
    key = None
    for line in request_text.split("\r\n"):
        if line.lower().startswith("sec-websocket-key:"):
            key = line.split(":", 1)[1].strip()
            break
    if key is None:
        print("WebSocket key not found")
        return False
    magic = "258EAFA5-E914-47DA-95CA-C5AB0DC85B11"
    sha1 = hashlib.sha1(
        (key + magic).encode()
    ).digest()
    accept_key = ubinascii.b2a_base64(
        sha1
    ).strip().decode()
    response = (
        "HTTP/1.1 101 Switching Protocols\r\n"
        "Upgrade: websocket\r\n"
        "Connection: Upgrade\r\n"
        "Sec-WebSocket-Accept: "
        + accept_key +
        "\r\n\r\n"
    )
    client.send(response.encode())
    return True
# RECEIVE WEBSOCKET FRAME
def receive_frame(client):
    header = recv_exact(client, 2)
    if header is None:
        return None
    byte1 = header[0]
    byte2 = header[1]
    opcode = byte1 & 0x0F
    # Close frame
    if opcode == 8:
        print("Close frame received")
        return None
    # Ping frame
    if opcode == 9:
        print("Ping received")
        length = byte2 & 0x7F
        if length == 126:
            extended = recv_exact(client, 2)
            length = (
                (extended[0] << 8)
                | extended[1]
            )
        mask = recv_exact(client, 4)
        payload = recv_exact(client, length)
        send_frame(client, "", 10)
        return ""
    # Text frame
    if opcode != 1:
        return ""
    masked = (byte2 & 0x80) != 0
    length = byte2 & 0x7F
    # Extended length
    if length == 126:
        extended = recv_exact(client, 2)
        length = (
            (extended[0] << 8)
            | extended[1]
        )
    elif length == 127:
        extended = recv_exact(client, 8)
        length = 0
        for byte in extended:
            length = (length << 8) | byte
    # Mask
    if masked:
        mask = recv_exact(client, 4)
    else:
        mask = None
    # Payload
    payload = recv_exact(client, length)
    if payload is None:
        return None
    # Unmask browser frame
    if masked:
        decoded = bytearray()
        for i in range(length):
            decoded.append(
                payload[i] ^
                mask[i % 4]
            )
        payload = bytes(decoded)
    return payload.decode()
# SEND WEBSOCKET FRAME
def send_frame(client, message, opcode=1):
    payload = message.encode()
    length = len(payload)
    first_byte = 0x80 | opcode
    if length < 126:
        frame = bytes([
            first_byte,
            length
        ]) + payload
    elif length < 65536:
        frame = (
            bytes([
                first_byte,
                126
            ])
            +
            length.to_bytes(2, "big")
            +
            payload
        )
    else:
        frame = (
            bytes([
                first_byte,
                127
            ])
            +
            length.to_bytes(8, "big")
            +
            payload
        )
    client.send(frame)
# CREATE SERVER SOCKET
address = socket.getaddrinfo(
    "0.0.0.0",
    80
)[0][-1]
server = socket.socket()
server.setsockopt(
    socket.SOL_SOCKET,
    socket.SO_REUSEADDR,
    1
)
server.bind(address)
server.listen(1)
print()
print("WebSocket server started")
print("Port: 80")
print()
print("Open this in your browser:")
print("http://" + ip)
print()
# MAIN LOOP
while True:
    print("Waiting for browser...")
    client, address = server.accept()
    print("Client connected:", address)
    try:
        request = client.recv(2048)
        if not request:
            client.close()
            continue
        # =================================================
        # WEBSOCKET REQUEST
        # =================================================
        if b"Upgrade: websocket" in request:
            print("WebSocket handshake received")
            success = websocket_handshake(
                client,
                request
            )
            if not success:
                client.close()
                continue
            print("WebSocket connection established")
            send_frame(
                client,
                "Connected"
            )
            # ---------------------------------------------
            # RECEIVE FRAMES
            # ---------------------------------------------
            while True:
                message = receive_frame(client)
                if message is None:
                    print("WebSocket disconnected")
                    break
                if message == "":
                    continue
                print()
                print("----------------------------")
                print("WEBSOCKET FRAME RECEIVED")
                print("----------------------------")
                print("Payload:", message)
                # ON
                if message.upper() == "ON":
                    led.on()
                    state = "ON"
                    print("LED: ON")
                    print("GPIO 25: HIGH")
                    send_frame(
                        client,
                        "LED is ON"
                    )
                # OFF
                elif message.upper() == "OFF":
                    led.off()
                    state = "OFF"
                    print("LED: OFF")
                    print("GPIO 25: LOW")
                    send_frame(
                        client,
                        "LED is OFF"
                    )
                else:
                    print("Unknown command")
                    send_frame(
                        client,
                        "Unknown command"
                    )
        # =================================================
        # NORMAL HTTP REQUEST
        # =================================================
        else:
            response = (
                "HTTP/1.1 200 OK\r\n"
                "Content-Type: text/html\r\n"
                "Connection: close\r\n"
                "\r\n"
                + html
            )
            client.send(response.encode())
            client.close()
    except Exception as e:
        print("Error:", e)
        try:
            client.close()
        except:
            pass
