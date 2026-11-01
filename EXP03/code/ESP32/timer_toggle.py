# Recovered from Screenshot 2026-08-24 115112.png.
from machine import Pin, Timer

led = Pin(2, Pin.OUT)  # Probe GPIO2 to observe the waveform.
timer = Timer(2)

def timer_callback(t):
    led.value(not led.value())  # One toggle per event; two events per cycle.

timer.init(
    freq=748,  # 748 toggles/s gives an ideal square-wave frequency of 374 Hz.
    mode=Timer.PERIODIC,
    callback=timer_callback,
)
# Run timer.deinit() in the console to stop the timer.
