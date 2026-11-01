# EXP06 Components and connections

This experiment is ESP32 only, as confirmed by the user. The PWM motor-control program is included with short explanatory comments; no STM32 program is required.

## ESP32 PWM through an L293 family motor driver

### Components

| Component | Quantity | Details |
| --- | --- | --- |
| Classic ESP32 development board | 1 |  |
| L293 family motor driver module | 1 | User confirms L293; report says L293D. Exact suffix, manufacturer and module terminal mapping remain unconfirmed. |
| DC motor | 1 | Rated voltage and stall current unspecified. |
| External regulated motor supply | 1 | Voltage/current depend on motor and driver; do not power motor from GPIO. |
| 5 V logic supply for L293 family driver | 1 | May be provided by a compatible module regulator; verify the exact part datasheet. |
| USB data cable | 1 |  |
| Jumper wires | As required |  |

### Connections

| From | To | Details |
| --- | --- | --- |
| ESP32 GPIO22 | L293 family driver EN1 or 1,2EN | PWM at 1000 Hz |
| ESP32 GPIO21 | L293 family driver IN1 or 1A |  |
| ESP32 GPIO18 | L293 family driver IN2 or 2A |  |
| DC motor terminal 1 | L293 family driver OUT1 or 1Y |  |
| DC motor terminal 2 | L293 family driver OUT2 or 2Y |  |
| Regulated 5 V logic supply | L293 family driver VCC1 | use module labels if using a breakout Check exact driver datasheet and module power labels. |
| Motor supply positive | L293 family driver VCC2 | match motor and driver ratings Check exact driver datasheet and module power labels. |
| ESP32 GND, motor supply negative and logic supply ground | L293 family driver GND | Common ground |
| ESP32 USB | PC USB |  |

### Notes

- The source omitted from machine import Pin, PWM; this clear missing import was restored.
- The stop function disables enable, allowing the outputs to become high impedance; it does not guarantee mechanical braking.
- Motor speed is affected by load and driver voltage drop; duty percentage is not measured RPM.
- The user identified an L293 family module, while the report calls it L293D. No exact IC pin mapping or protection arrangement is asserted until its suffix and module labels are confirmed.
- A bare L293 needs external high-speed clamp diodes; L293D integrates clamp diodes. Verify what is fitted on the actual module.

See the [experiment README](README.md) for setup, expected behavior and missing items.

## Sources

Archive paths below refer to the supplied IoT ZIP. User contributions are identified separately.

- IOT/EXP6/EXP6_2024300174_A.docx
- IOT/EXP6/6th.docx
- IOT/EXP6/EXP6_2024300174_A.pdf
- IOT/EXP6/IMG20260923162120.jpg
- IOT/EXP6/Screenshot 2026-09-23 162926.png
- IOT/EXP6/Screenshot 2026-09-23 162952.png
- User confirmation of an L293 motor driver on 1 November 2026
- User confirmation that Experiment 6 is ESP32 only on 1 November 2026

### Technical references

- [Texas Instruments L293 and L293D datasheet](https://www.ti.com/lit/ds/symlink/l293.pdf)
