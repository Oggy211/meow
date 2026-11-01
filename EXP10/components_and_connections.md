# EXP10 Components and connections

One complete ESP32 program performs both soil-sensor acquisition and BLE phone notification. These are stages of the same program, not separate board implementations.

## Single implementation Sensor acquisition and BLE phone notifications

### Components

| Component | Quantity | Details |
| --- | --- | --- |
| Classic ESP32 development board | 1 | Firmware must include the bluetooth module; selected board must support BLE. |
| Resistive two-prong soil moisture probe and analog interface module | 1 set | Standalone photograph probe is marked HW-080; interface module electrical specification is not readable. |
| Jumper leads | 3 plus probe leads |  |
| USB data cable and computer with Thonny | 1 each |  |
| Smartphone with BLE and LightBlue or nRF Connect | 1 |  |
| Dry and moist soil samples | 1 each | Use for calibration rather than assuming a universal threshold. |

### Connections

| From | To | Details |
| --- | --- | --- |
| Probe two terminals | Sensor interface two-pin probe connector | Probe goes to the interface module, not directly to the GPIO. |
| Sensor module VCC | ESP32 3V3 | Use a module verified to operate at 3.3 V. |
| Sensor module GND | ESP32 GND |  |
| Sensor module AO analog output | ESP32 GPIO34 | The code reads ADC on GPIO34. DO is unused. Verify output remains within the ESP32 input limits. |
| ESP32 USB | PC USB |  |
| ESP32 BLE | Phone BLE app | Wireless; no signal cable between phone and board. |

### Notes

- This report documents one complete program, not two separate code parts; acquisition and BLE communication are included in that one file.
- The value is a raw ADC count, not calibrated soil-moisture percentage. A value of 4095 may indicate saturation or an open/dry sensor, so verify wiring and calibration.
- ADC.ATTN_11DB widens the measurement range; it does not make GPIO34 tolerant of 5 V.
- GPIO34 is input-only on classic ESP32; use it for sensor input, not LED output.
- The source has no pump or relay driver and does not irrigate automatically.
- Resistive probes are suitable for this demonstration; prolonged powered use can degrade exposed electrodes.

See the [experiment README](README.md) for setup, expected behavior and missing items.

## Sources

Archive paths below refer to the supplied IoT ZIP. User contributions are identified separately.

- IOT/EXP10/EXP10_2024300174_IOT.docx
- IOT/EXP10/IMG20261012171012.jpg
- IOT/EXP10 BLE app screenshots and embedded hardware and terminal photos

### Technical references

- [MicroPython ESP32 quick reference](https://www.micropython.org/resources/docs/en/latest/esp32/quickref.html)
- [MicroPython low level Bluetooth](https://docs.micropython.org/en/latest/library/bluetooth.html)
- [MicroPython umqtt simple README](https://github.com/micropython/micropython-lib/blob/master/micropython/umqtt.simple/README.rst)
- [Mosquitto authentication methods](https://mosquitto.org/documentation/authentication-methods/)
- [Mosquitto configuration reference](https://mosquitto.org/man/mosquitto-conf-5.html)
