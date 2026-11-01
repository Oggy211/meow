# EXP07 Viva questions and answers

13 short questions covering the documented experiment.

## 1 What does the DHT11 measure?

Temperature and relative humidity.

## 2 Is its output analog?

No. It sends digital data over its data line using the DHT protocol.

## 3 Which ESP32 pin reads the sensor?

GPIO14 in the supplied report and screenshot.

## 4 What is the role of the ESP32?

It reads the sensor, connects to Wi-Fi and sends data to the cloud.

## 5 What is ThingSpeak?

An IoT platform that stores channel data and displays it in charts.

## 6 Which fields are used?

Field 1 is temperature and Field 2 is humidity.

## 7 What is the Write API key for?

It authorizes writing data to a channel.

## 8 How does the report send data?

It describes an HTTP request to the ThingSpeak update API.

## 9 What does a nonzero entry ID indicate?

The API accepted a channel update; a response body of 0 indicates failure.

## 10 Does HTTP status 200 alone prove the update succeeded?

No. Check the API response body as well.

## 11 Why wait between cloud uploads?

ThingSpeak limits update frequency; use the interval allowed by the account.

## 12 Why can the sensor work while upload fails?

Wi-Fi, DNS, Internet access, credentials, API parameters or cloud limits may fail independently.

## 13 Why should an HTTP response be closed?

Closing it releases the underlying socket and memory.

See the [experiment README](README.md) for the available code and its limitations.

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
