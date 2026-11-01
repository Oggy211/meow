# EXP07 Components and connections

A complete [exp7.py](code/ESP32/exp7.py) now reads the DHT11 and uploads both fields. The off-screen loop was completed from the documented setup at the user's request. This experiment has one documented ESP32 implementation.

## ESP32 sensor acquisition and ThingSpeak upload

### Components

| Component | Quantity | Details |
| --- | --- | --- |
| Classic ESP32 development board | 1 |  |
| DHT11 sensor module | 1 | Three pin module visible in photo. |
| USB data cable | 1 |  |
| Jumper wires | 3 |  |
| Wi-Fi network and Internet access | 1 |  |
| ThingSpeak channel | 1 | Field 1 temperature; Field 2 humidity; own Write API key. |

### Connections

| From | To | Details |
| --- | --- | --- |
| ESP32 3V3 | DHT11 module VCC | Use a sensor module compatible with 3.3 V power/logic. |
| ESP32 GND | DHT11 module GND |  |
| ESP32 GPIO14 | DHT11 module DATA | The photographed module has support components; a bare sensor needs appropriate data pull-up. |
| ESP32 USB | PC USB |  |
| ESP32 Wi-Fi | Internet and ThingSpeak channel | Logical network connection, not a jumper wire. |

### Notes

- GPIO14, DHT11, temperature in Field 1 and humidity in Field 2 follow the supplied evidence. The completed upload loop attempts an update every 20 seconds.
- This experiment is ESP32 based in the report; there is no separate STM32 part.
- The screenshot contains private credentials; reusable code uses placeholders instead.

See the [experiment README](README.md) for setup, expected behavior and missing items.

## Sources

Archive paths below refer to the supplied IoT ZIP. User contributions are identified separately.

- IOT/EXP7/EXP7_2024300174_A.docx
- IOT/EXP7/EXP7_2024300174_A.docx.pdf
- IOT/EXP1/EXP7_2024300174_A.docx
- IOT/EXP7/Screenshot 2026-09-30 162049.png
- IOT/EXP7/Screenshot 2026-09-30 162034.png
- IOT/EXP7/IMG-20260930-WA0018.jpeg

### Technical references

- [ThingSpeak Write Data API](https://www.mathworks.com/help/thingspeak/writedata.html)
- [ThingSpeak channel update intervals](https://www.mathworks.com/help/thingspeak/channel-control.html)

Additional source: two screenshots supplied in chat on 1 November 2026. The completion is described in the [experiment README](README.md).
