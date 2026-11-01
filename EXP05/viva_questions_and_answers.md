# EXP05 Viva questions and answers

Analog sensor reading displayed on an I2C OLED. Questions cover the documented STM32 and ESP32 implementations.

[Experiment overview](README.md) | [Components and connections](components_and_connections.md)

## 1 What is I2C?

A synchronous serial bus that uses SDA for data and SCL for clock.

## 2 Which device controls the clock?

The microcontroller acts as the controller and normally generates SCL.

## 3 Which device uses I2C in this implementation?

The SSD1306 OLED; the potentiometer is measured through ADC.

## 4 Why do I2C lines need pull-ups?

The devices pull the open-drain lines low and the resistors return them high.

## 5 What is the ESP32 OLED address?

0x3C in the supplied program.

## 6 What pins are used for the ESP32 OLED?

GPIO22 for SCL and GPIO21 for SDA.

## 7 What pins are used for the STM32 OLED?

PB8 for I2C1 SCL and PB9 for I2C1 SDA.

## 8 Can multiple I2C devices share the same two wires?

Yes, when their addresses and electrical requirements allow it.

## 9 What does an I2C scan check?

It lists addresses that acknowledge on the bus.

## 10 Why does OLED code clear the screen before writing?

It removes the previous content from the framebuffer so old digits do not remain.

## 11 What sends the ESP32 framebuffer to the OLED?

oled.show().

## 12 How is potentiometer percentage calculated?

Raw count times 100 divided by 4095, assuming a full-scale 12 bit reading.

## 13 What should be checked if the OLED stays blank?

Power, common ground, SDA/SCL wiring, pull-ups, I2C address, display size and driver compatibility.

## Sources

Archive paths below identify the evidence in the supplied ZIP; the original reports and media are not copied into this code folder.

- `IOT/EXP5/EXP5_2024300174_A.docx`
- `IOT/EXP5/IMG20260923165847.jpg`
- `IOT/EXP5/IMG20260923165900.jpg`
- `IOT/EXP5/IMG20261013164808.jpg`
- `IOT/EXP5/IMG20261013164823.jpg`
- User-supplied STM32 ssd1306.c attachment and ssd1306.h chat text on 1 November 2026

Technical references:

- [MicroPython ESP32 ADC reference](https://www.micropython.org/resources/docs/en/latest/esp32/quickref.html)
- [Official MicroPython SSD1306 driver](https://github.com/micropython/micropython-lib/tree/master/micropython/drivers/display/ssd1306)
