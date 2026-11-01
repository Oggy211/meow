# Experiment 5 ESP32 ADC reading shown on an SSD1306 OLED.
# Upload the separate ssd1306.py driver first; it is absent from the archive.
from machine import ADC, Pin, SoftI2C
from ssd1306 import SSD1306_I2C
import time
# ADC setup
adc = ADC(Pin(34))
adc.atten(ADC.ATTN_11DB)
# I2C setup
i2c = SoftI2C(
    scl=Pin(22),
    sda=Pin(21),
    freq=100000
)
# OLED setup
oled = SSD1306_I2C(128, 64, i2c, addr=0x3C)
# Main loop
while True:
    # Read ADC value
    adc_value = adc.read()
    # Convert ADC value to voltage
    voltage = (adc_value / 4095) * 3.3
    # Clear OLED
    oled.fill(0)
    # Display values
    oled.text("ADC SENSOR", 25, 5)
    oled.text("ADC: " + str(adc_value), 5, 25)
    oled.text("Voltage:", 5, 42)
    oled.text("{:.2f} V".format(voltage), 75, 42)
    # Update OLED
    oled.show()
    # Wait 1 second
    time.sleep(1)
