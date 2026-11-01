# EXP06 Viva questions and answers

14 short questions covering the documented experiment.

## 1 What is PWM?

A repeating digital signal whose on-time fraction is varied to control average drive.

## 2 What is duty cycle?

On-time divided by total period, multiplied by 100 percent.

## 3 What PWM frequency does the source use?

1000 Hz, so each period is 1 ms.

## 4 What does duty_u16 accept?

An integer from 0 to 65535, representing zero to full duty.

## 5 What value represents about 50 percent duty?

About 32767 or 32768.

## 6 Why use an L293D?

It drives the motor current and allows bidirectional control through an H bridge.

## 7 Which pin controls speed?

GPIO22 drives the driver enable input with PWM.

## 8 Which pins control direction?

GPIO21 and GPIO18 drive IN1 and IN2.

## 9 What input combination is forward in the code?

IN1 is high and IN2 is low; actual physical direction depends on motor wire order.

## 10 Why must grounds be common?

The driver must interpret the ESP32 logic levels against the same reference.

## 11 Is 50 percent duty equal to 50 percent RPM?

No. Actual speed also depends on load, supply, motor properties and driver loss.

## 12 What happens at low duty?

The motor may not start because torque can be insufficient to overcome load and friction.

## 13 What happens when stop_motor is called?

Enable duty becomes zero, direction pins go low, and the driver outputs are disabled.

## 14 Why stop before reversing?

Allowing the rotor to slow reduces sudden current and mechanical stress.

See the [experiment README](README.md) for the available code and its limitations.

## Sources

Archive paths below refer to the supplied IoT ZIP. User contributions are identified separately.

- IOT/EXP6/EXP6_2024300174_A.docx
- IOT/EXP6/6th.docx
- IOT/EXP6/EXP6_2024300174_A.pdf
- IOT/EXP6/IMG20260923162120.jpg
- IOT/EXP6/Screenshot 2026-09-23 162926.png
- IOT/EXP6/Screenshot 2026-09-23 162952.png
- User confirmation of an L293 motor driver on 1 November 2026

### Technical references

- [Texas Instruments L293 and L293D datasheet](https://www.ti.com/lit/ds/symlink/l293.pdf)
