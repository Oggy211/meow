# Recovered from Screenshot 2026-08-03 172709.png.
from machine import Pin
from time import sleep

button = Pin(4, Pin.IN)  # Source uses an external bias resistor, not PULL_DOWN.
led = Pin(16, Pin.OUT)

while True:
    if button.value() == 1:  # Active-high button: pressed connects input to 3.3 V.
        led.on()
        print("Button Pressed")
    else:
        led.off()
        print("Button Released")
    sleep(0.1)  # Limit polling and console output.
