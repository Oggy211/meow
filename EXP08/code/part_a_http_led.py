# EXP08 Part A: HTTP LED control in access-point mode.
# Save only this program as main.py on the ESP32. LED pin is GPIO2.
import network
import socket
import time
from machine import Pin
# Configure LED on GPIO 2
led = Pin(2, Pin.OUT)
led.value(0)
# Configure Wi-Fi access point
ssid = "ESP32-WebServer"
password = "SET_AP_PASSWORD"  # Set an access-point password of at least 8 characters.
ap = network.WLAN(network.AP_IF)
ap.active(True)
ap.config(essid=ssid, password=password)
while not ap.active():
    time.sleep(0.1)
ip = ap.ifconfig()[0]
print("Wi-Fi:", ssid)
print("Password:", password)
print("Open browser at: http://" + ip)
# Create HTTP server
server = socket.socket()
server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
server.bind(("0.0.0.0", 80))
server.listen(5)
def webpage():
    state = "ON" if led.value() else "OFF"
    return """<!DOCTYPE html>
<html>
<head>
<title>ESP32 Web Server</title>
<meta name="viewport" content="width=device-width, initial-scale=1">
</head>
<body style="text-align:center;font-family:Arial">
<h1>ESP32 LED Control</h1>
<p>LED State: <b>""" + state + """</b></p>
<p><a href="/?led=on"><button>LED ON</button></a></p>
<p><a href="/?led=off"><button>LED OFF</button></a></p>
</body>
</html>"""
# Handle browser requests
while True:
    conn, addr = server.accept()
    try:
        request = conn.recv(1024).decode()
        print("Request received:", request.split("\r\n")[0])
        if "GET /?led=on " in request:
            led.value(1)
            print("LED switched ON")
        elif "GET /?led=off " in request:
            led.value(0)
            print("LED switched OFF")
        body = webpage()
        response = (
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: text/html\r\n"
            "Connection: close\r\n"
            "\r\n" + body
        )
        conn.sendall(response.encode())
    except Exception as e:
        print("Error:", e)
    finally:
        conn.close()
