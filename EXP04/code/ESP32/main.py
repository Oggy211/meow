# Experiment 4: code transcribed from Screenshot 2026-08-24 122630.png.
# The source does not configure attenuation; its voltage is a lab approximation.
from machine import ADC, Pin
from time import sleep

adc = ADC(Pin(34))  # Read the potentiometer wiper on ADC1 GPIO34.

while True:
    adc_value = adc.read()  # Original ESP32 API: a raw 12-bit reading.
    voltage = (adc_value / 4095) * 3.3  # Not a calibrated voltage measurement.
    print("ADC Value: ", adc_value)
    print("Voltage: ", voltage, "V")
    sleep(1)  # Print one reading each second.
