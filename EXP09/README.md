# EXP09 MQTT sensor data using Mosquitto and MQTTX

## Aim

Publish ESP32 digital IR sensor readings through a Mosquitto MQTT broker and observe them with MQTTX or a matching subscriber.

## Part status

The IR publisher and the original ultrasonic-topic subscriber are preserved separately. The optional IR subscriber is an explicitly labeled adaptation that matches the supplied IR publisher.

## Files

- [Components and connections](components_and_connections.md)
- [Viva questions and answers](viva_questions_and_answers.md)

## Part A IR publisher with Mosquitto and MQTTX

### Code

- [part_a_ir_publisher.py](code/part_a_ir_publisher.py)

### Setup

1. Use a classic ESP32 development board with MicroPython firmware and a USB data cable. GPIO numbers are chip GPIO numbers, not physical header positions.
2. Open the file in Thonny with the MicroPython ESP32 interpreter selected; save the chosen program on the device as main.py or run it interactively. Run one program at a time on each board.
3. Install umqtt.simple on each ESP32 that runs an MQTT program; it is a MicroPython library, not a standard desktop Python dependency.
4. Install/start Mosquitto on the PC with a listener reachable from the ESP32 on TCP port 1883, and choose the appropriate authentication for that listener. The supplied client code has no MQTT username/password fields.
5. Set YOUR_PC_LAN_IP to the broker PC LAN address and enter Wi-Fi credentials. Allow the intended local TCP 1883 traffic through the PC firewall.
6. In MQTTX create a connection to the same broker address and port with a unique client ID. Subscribe to sensor_data before observing the ESP32 publisher.
7. Move an object near and away from the IR sensor; record whether detection corresponds to 0 or 1 for your module.

### Expected behavior

The ESP32 samples GPIO27 every second and publishes the raw digital value as text on sensor_data. MQTTX receives matching messages through Mosquitto.

### Notes

- The report required-hardware list mentions DHT11/ultrasonic and its drawing shows ultrasonic plus buzzer; the actual publisher code and hardware photograph use an IR module. This part follows the actual IR code.
- This source uses the default QoS 0 and no reconnect handling. A lost connection can stop the program.
- The original publisher and subscriber had different broker IPs and topics; they are not a matching end-to-end pair as printed.

## Part B Source subscriber and optional matching IR adaptation

### Code

- [part_b_ultrasonic_subscriber_source.py](code/part_b_ultrasonic_subscriber_source.py)
- [optional_paired_ir_subscriber.py](code/optional_paired_ir_subscriber.py)

### Setup

1. Use a classic ESP32 development board with MicroPython firmware and a USB data cable. GPIO numbers are chip GPIO numbers, not physical header positions.
2. Open the file in Thonny with the MicroPython ESP32 interpreter selected; save the chosen program on the device as main.py or run it interactively. Run one program at a time on each board.
3. For the exact source variant, run part_b_ultrasonic_subscriber_source.py and provide a publisher using the source topic anshul/ultrasonic.
4. For a complete IR demonstration, run optional_paired_ir_subscriber.py on the second board; it intentionally adapts the topic to sensor_data and labels values as IR.
5. Use identical broker settings in the paired publisher and subscriber, with distinct client IDs. Install umqtt.simple on both boards.

### Expected behavior

The subscriber registers a callback, subscribes to a topic and calls check_msg repeatedly to print messages. The optional paired IR adaptation receives the supplied IR publisher values.

### Notes

- Do not run publisher and subscriber files sequentially on the same board expecting concurrent execution: each has an infinite main loop. Use two boards or MQTTX as the receiver.
- The ultrasonic subscriber does not measure distance itself and has no local ultrasonic sensor connection.
- A matching ultrasonic publisher is outside the recovered EXP9 code; request it from the user if that independent setup must be reproduced.

## Missing information

- The independent ultrasonic publisher for anshul/ultrasonic is not included in EXP9. It is unnecessary for the documented IR publisher plus MQTTX or optional IR subscriber demonstration.

## Source changes

- Transcribed the publisher and subscriber into clean Python with short explanatory comments.
- Removed page headers, footers and the conclusion that interrupted subscriber extraction; restored the continuous program order.
- Replaced source classroom Wi-Fi credentials and the differing broker IPs with explicit configuration placeholders.
- Preserved original subscriber topic anshul/ultrasonic. Added optional_paired_ir_subscriber.py as a clearly labeled adaptation using sensor_data and an IR output label.

## Sources

Archive paths below refer to the supplied IoT ZIP. User contributions are identified separately.

- IOT/EXP9/2024300208_EXP_9_IOT.pdf pages 1 to 7

### Technical references

- [MicroPython ESP32 quick reference](https://www.micropython.org/resources/docs/en/latest/esp32/quickref.html)
- [MicroPython low level Bluetooth](https://docs.micropython.org/en/latest/library/bluetooth.html)
- [MicroPython umqtt simple README](https://github.com/micropython/micropython-lib/blob/master/micropython/umqtt.simple/README.rst)
- [Mosquitto authentication methods](https://mosquitto.org/documentation/authentication-methods/)
- [Mosquitto configuration reference](https://mosquitto.org/man/mosquitto-conf-5.html)
