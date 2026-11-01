# EXP10 Soil moisture monitoring and BLE watering alerts

## Aim

Read an analog soil-moisture sensor and send the raw reading and a watering-status message to a phone over BLE.

## Part status

One complete ESP32 program performs both soil-sensor acquisition and BLE phone notification. These are stages of the same program, not separate board implementations.

## Files

- [Components and connections](components_and_connections.md)
- [Viva questions and answers](viva_questions_and_answers.md)

## Single implementation Sensor acquisition and BLE phone notifications

### Code

- [soil_moisture_ble.py](code/soil_moisture_ble.py)

### Setup

1. Use a classic ESP32 development board with MicroPython firmware and a USB data cable. GPIO numbers are chip GPIO numbers, not physical header positions.
2. Open the file in Thonny with the MicroPython ESP32 interpreter selected; save the chosen program on the device as main.py or run it interactively. Run one program at a time on each board.
3. Check module pin labels; AO and DO are different outputs. Use AO for this program.
4. Measure raw readings for dry and wet samples, then adjust DRY_THRESHOLD = 3000 and verify that a larger value actually means drier soil. Reverse the comparison if your module behaves oppositely.
5. Run soil_moisture_ble.py. In the phone BLE app scan for ESP32-Soil and connect.
6. Open service UUID 12345678-1234-5678-1234-56789abcdef0. Raw ADC characteristic ends in f1 and status characteristic ends in f2. Enable notifications/subscribe in the app to monitor the updates. Display bytes as UTF-8 text.

### Expected behavior

Every two seconds, GPIO34 ADC is read. Raw values at or above 3000 produce WATER REQUIRED; lower values produce WATER NOT REQUIRED. Latest raw and status values are stored as readable GATT characteristic values and sent as BLE notifications to connected phones.

### Notes

- This report documents one complete program, not two separate code parts; acquisition and BLE communication are included in that one file.
- The value is a raw ADC count, not calibrated soil-moisture percentage. A value of 4095 may indicate saturation or an open/dry sensor, so verify wiring and calibration.
- ADC.ATTN_11DB widens the measurement range; it does not make GPIO34 tolerant of 5 V.
- GPIO34 is input-only on classic ESP32; use it for sensor input, not LED output.
- The source has no pump or relay driver and does not irrigate automatically.
- Resistive probes are suitable for this demonstration; prolonged powered use can degrade exposed electrodes.

## Missing information

- No complete code is missing. Exact interface module specification is unreadable, so verify 3.3 V operation and analog output limits before wiring.

## Source changes

- Recovered the complete MicroPython program and retained GPIO34, threshold 3000, UUIDs and two-second reporting interval.
- Added two brief opening comments and removed decorative comment dividers; behavior was preserved.

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
