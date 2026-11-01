# Recovered from Screenshot 2026-08-03 165507.png.
from machine import Pin
from time import sleep

led = Pin(16, Pin.OUT)  # External LED on GPIO16 through a series resistor.

while True:
    led.on()
    print("LED ON")
    sleep(1)  # One second on.
    led.off()
    print("LED OFF")
    sleep(1)  # One second off.
