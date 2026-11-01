# EXP09 Viva questions and answers

14 short questions covering the documented experiment.

## 1 What is MQTT?

A lightweight messaging protocol that uses a broker and topic-based publish-subscribe communication.

## 2 What are the roles in this experiment?

The ESP32 IR code publishes; Mosquitto brokers messages; MQTTX or an ESP32 subscriber receives them.

## 3 What is an MQTT topic?

A string used to route messages. A subscriber receives publications that match its subscription.

## 4 Which topic carries the actual IR publisher data?

sensor_data. The supplied ultrasonic subscriber instead uses anshul/ultrasonic.

## 5 Why did the original publisher and subscriber not form a pair?

Their broker addresses and topics differed. Both must refer to the intended broker and matching topic.

## 6 Which sensor pin is read?

The IR module digital OUT is read on GPIO27.

## 7 Does a value of zero always mean no obstacle?

No. Many modules are active low. Check the actual module and demonstrate its polarity.

## 8 Why is a unique client ID necessary?

A broker identifies a connection by its client ID; reusing an ID can disconnect the earlier client.

## 9 What does QoS 0 mean?

At most once delivery with no MQTT acknowledgement or retry guarantee.

## 10 What does check_msg do?

It checks for an incoming message and invokes the registered callback when a subscribed message arrives.

## 11 Why use bytes for the topic and payload?

umqtt.simple uses byte strings for MQTT message data to reduce conversion and memory overhead.

## 12 Can MQTTX replace the second ESP32?

Yes. MQTTX can subscribe and display the published data on the PC.

## 13 What is the conventional unencrypted MQTT port?

TCP 1883. It does not provide TLS encryption by itself.

## 14 Why does a broker on the PC fail from ESP32 if it works locally?

It may listen only on loopback, reject remote authentication, be blocked by the firewall, or be unreachable due to LAN isolation.

See the [experiment README](README.md) for the available code and its limitations.

## Sources

Archive paths below refer to the supplied IoT ZIP. User contributions are identified separately.

- IOT/EXP9/2024300208_EXP_9_IOT.pdf pages 1 to 7

### Technical references

- [MicroPython ESP32 quick reference](https://www.micropython.org/resources/docs/en/latest/esp32/quickref.html)
- [MicroPython low level Bluetooth](https://docs.micropython.org/en/latest/library/bluetooth.html)
- [MicroPython umqtt simple README](https://github.com/micropython/micropython-lib/blob/master/micropython/umqtt.simple/README.rst)
- [Mosquitto authentication methods](https://mosquitto.org/documentation/authentication-methods/)
- [Mosquitto configuration reference](https://mosquitto.org/man/mosquitto-conf-5.html)
