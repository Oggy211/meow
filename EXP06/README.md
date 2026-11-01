# EXP06 PWM generation for DC motor speed and direction control

## Aim

Generate PWM on the ESP32 and use an L293 family motor driver to vary DC motor drive and direction.

## Part status

This experiment is ESP32 only, as confirmed by the user. The PWM motor-control program is included with short explanatory comments; no STM32 program is required.

## Files

- [Components and connections](components_and_connections.md)
- [Viva questions and answers](viva_questions_and_answers.md)

## ESP32 PWM through an L293 family motor driver

### Code

- [main.py](code/ESP32/main.py)

### Setup

1. Flash compatible MicroPython onto the classic ESP32 board and connect through Thonny.
2. Upload only this experiment main.py when selecting that experiment.
3. Verify the driver module pin names and any enable jumpers before applying power.
4. Connect motor power separately and join all grounds. Check the motor stall current against the driver rating.
5. Use f for forward, r for reverse, s for stop, 1 to 5 for 10/25/50/75/90 percent duty and x to exit.
6. Stop the motor and allow it to slow before changing direction.
7. Confirm the exact L293 or L293D suffix and module schematic. A bare L293 requires external high-speed clamp diodes; L293D includes them. A module may already provide protection, so verify its circuit.

### Expected behavior

Starts stopped; user commands set direction and duty cycle. Stored speed starts at 50 percent.

### Notes

- The source omitted from machine import Pin, PWM; this clear missing import was restored.
- The stop function disables enable, allowing the outputs to become high impedance; it does not guarantee mechanical braking.
- Motor speed is affected by load and driver voltage drop; duty percentage is not measured RPM.
- The user identified an L293 family module, while the report calls it L293D. No exact IC pin mapping or protection arrangement is asserted until its suffix and module labels are confirmed.
- A bare L293 needs external high-speed clamp diodes; L293D integrates clamp diodes. Verify what is fitted on the actual module.

## Missing information

- DC motor rated voltage and stall current.
- Motor supply voltage/current and driver exact suffix and module connection labels.

## Source changes

- Corrected the scope to ESP32 only following the user confirmation on 1 November 2026.
- Restored the missing from machine import Pin, PWM line.
- Removed decorative comment separators while retaining short explanatory comments and source control logic.
- Updated motor driver to user-confirmed L293 family and removed assumed bare-IC pin numbers; L293 versus L293D clamp-diode difference is explicit.

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
