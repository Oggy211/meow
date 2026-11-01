# EXP04 Viva questions and answers

Analog input acquisition using ADC. Questions cover the documented STM32 and ESP32 implementations.

[Experiment overview](README.md) | [Components and connections](components_and_connections.md)

## 1 What does an ADC do?

It converts an analog input voltage into a digital number.

## 2 How many levels does a 12 bit ADC have?

4096 levels, usually numbered 0 to 4095.

## 3 Why use a potentiometer here?

Its wiper produces an adjustable voltage to demonstrate the ADC range.

## 4 Which analog input is used on each board?

STM32 uses ADC1 channel 0, mapped to PA0 for the documented F4 configuration; ESP32 uses GPIO34.

## 5 How is the STM32 voltage estimated?

Voltage in millivolts is raw count times 3300 divided by 4095, assuming a 3.3 V reference.

## 6 What is the approximate 12 bit quantization step for a 3.3 V range?

About 0.806 mV; the ideal code step is 3.3/4096 V.

## 7 Why do readings fluctuate?

Noise, reference variation, wiring and ADC sampling can change the measured code.

## 8 What does HAL_ADC_PollForConversion do?

It waits for a conversion to complete or for the timeout.

## 9 Is resolution the same as accuracy?

No. Resolution describes digital step size; accuracy describes agreement with the real voltage.

## 10 Why is a common ground required?

The input voltage must be measured relative to the same electrical reference.

## 11 Why is the ESP32 voltage formula approximate?

The input range depends on attenuation and calibration, and the ADC is not perfectly linear.

## 12 How could the measurements be improved?

Configure suitable attenuation and sampling, calibrate against a known voltage, improve grounding, and average readings.

## Sources

Archive paths below identify the evidence in the supplied ZIP; the original reports and media are not copied into this code folder.

- `IOT/EXP4/4th.docx`
- `IOT/EXP4/EXP4_2024300174_A.pdf`
- `IOT/EXP4/Screenshot 2026-08-24 122630.png`
- `IOT/EXP4/IMG20260824175952.jpg`
- `IOT/EXP4/IMG_20261005_001156.jpg`

Technical references:

- [MicroPython ESP32 ADC reference](https://www.micropython.org/resources/docs/en/latest/esp32/quickref.html)
