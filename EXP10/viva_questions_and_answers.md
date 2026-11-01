# EXP10 Viva questions and answers

14 short questions covering the documented experiment.

## 1 What is the aim of this experiment?

Read soil sensor data with ESP32 and send a watering status alert to a phone over BLE.

## 2 Which ESP32 pin reads the sensor?

GPIO34, using its ADC input.

## 3 Which module output is connected and why?

AO, because the code measures an analog voltage. DO is only a thresholded digital output.

## 4 What does an ADC do?

It converts an analog voltage into a numerical digital reading.

## 5 What is the decision threshold in the supplied code?

3000 raw counts. At or above it the status is WATER REQUIRED.

## 6 Is 3000 a universal dry-soil threshold?

No. It must be calibrated for the sensor, supply voltage, soil and measurement conditions.

## 7 Is the raw ADC reading a moisture percentage?

No. Percentage requires calibration and a suitable conversion model.

## 8 What is the purpose of attenuation?

It adjusts the ADC input measurement range. It does not protect against an overvoltage.

## 9 What are the BLE central and peripheral here?

The phone is the central and the advertising ESP32 is the peripheral.

## 10 What is a GATT service?

A grouping of related characteristics exposed by a BLE device.

## 11 What is a UUID?

An identifier used to distinguish a service or characteristic; this program uses custom 128-bit UUIDs.

## 12 What is the difference between a BLE read and a notification?

A read is requested by the phone. A notification pushes an update from the ESP32 without a separate application read request.

## 13 Why does advertising restart on disconnect?

It allows another phone connection after the previous connection ends.

## 14 Does the program turn on a water pump?

No. It only measures and sends messages; pump control would need additional code and an appropriate driver.

See the [experiment README](README.md) for the available code and its limitations.

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
