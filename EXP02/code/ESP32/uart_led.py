# Recovered from Screenshot 2026-08-17 164103.png.
from machine import UART, Pin
import time

uart = UART(2, baudrate=9600, tx=17, rx=16)  # USB-TTL adapter uses these pins.
led = Pin(2, Pin.OUT)  # The photographed board has an LED on GPIO2.

print("UART Ready")  # This goes to the MicroPython console.
uart.write("ESP32 UART Ready\r\n")  # This goes through UART2.

while True:
    if uart.any():
        data = uart.read(1)  # Commands are one-byte bytes objects.
        if data == b'1':
            led.on()
            print("LED ON")
            uart.write("LED ON\r\n")
        elif data == b'0':
            led.off()
            print("LED OFF")
            uart.write("LED OFF\r\n")
    time.sleep(0.1)
