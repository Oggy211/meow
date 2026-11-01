# EXP09 Components and connections

The IR publisher and the original ultrasonic-topic subscriber are preserved separately. The optional IR subscriber is an explicitly labeled adaptation that matches the supplied IR publisher.

## Part A IR publisher with Mosquitto and MQTTX

### Components

| Component | Quantity | Details |
| --- | --- | --- |
| ESP32 development board | 1 |  |
| Digital IR obstacle sensor module | 1 | Photograph shows an IR module; exact model and active polarity are not established. |
| Jumper leads | 3 |  |
| Computer with Thonny Mosquitto and MQTTX | 1 |  |
| USB data cable | 1 |  |
| Shared Wi-Fi LAN | 1 |  |

### Connections

| From | To | Details |
| --- | --- | --- |
| IR module VCC | ESP32 3V3 | Use a module documented to operate at 3.3 V; verify pin labels and supply rating. |
| IR module GND | ESP32 GND |  |
| IR module digital OUT | ESP32 GPIO27 | Never apply a 5 V output directly to the ESP32. Use a suitable level shifter if required. |
| ESP32 USB | PC USB |  |
| ESP32 and MQTTX PC | Same reachable Wi-Fi LAN | Wireless MQTT traffic goes to the PC broker LAN IP, not 127.0.0.1. |

### Notes

- The report required-hardware list mentions DHT11/ultrasonic and its drawing shows ultrasonic plus buzzer; the actual publisher code and hardware photograph use an IR module. This part follows the actual IR code.
- This source uses the default QoS 0 and no reconnect handling. A lost connection can stop the program.
- The original publisher and subscriber had different broker IPs and topics; they are not a matching end-to-end pair as printed.

## Part B Source subscriber and optional matching IR adaptation

### Components

| Component | Quantity | Details |
| --- | --- | --- |
| Second ESP32 development board | 1 | Needed only for an ESP32 subscriber; MQTTX alone can be the receiver. |
| USB data cable and Thonny | 1 each |  |
| Shared Wi-Fi LAN and running Mosquitto broker | 1 |  |
| Ultrasonic publisher on anshul/ultrasonic | Existing external device | Only needed for the preserved original subscriber. No corresponding ultrasonic publisher code is in this experiment report. |

### Connections

| From | To | Details |
| --- | --- | --- |
| Subscriber ESP32 USB | PC USB | Power/programming and message display; no local sensor wiring is required. |
| Subscriber ESP32 Wi-Fi | Broker LAN | Configure same broker address as the publisher you intend to receive. |

### Notes

- Do not run publisher and subscriber files sequentially on the same board expecting concurrent execution: each has an infinite main loop. Use two boards or MQTTX as the receiver.
- The ultrasonic subscriber does not measure distance itself and has no local ultrasonic sensor connection.
- A matching ultrasonic publisher is outside the recovered EXP9 code; request it from the user if that independent setup must be reproduced.

See the [experiment README](README.md) for setup, expected behavior and missing items.

## Sources

Archive paths below refer to the supplied IoT ZIP. User contributions are identified separately.

- IOT/EXP9/2024300208_EXP_9_IOT.pdf pages 1 to 7

### Technical references

- [MicroPython ESP32 quick reference](https://www.micropython.org/resources/docs/en/latest/esp32/quickref.html)
- [MicroPython low level Bluetooth](https://docs.micropython.org/en/latest/library/bluetooth.html)
- [MicroPython umqtt simple README](https://github.com/micropython/micropython-lib/blob/master/micropython/umqtt.simple/README.rst)
- [Mosquitto authentication methods](https://mosquitto.org/documentation/authentication-methods/)
- [Mosquitto configuration reference](https://mosquitto.org/man/mosquitto-conf-5.html)
