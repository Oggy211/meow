# Experiment 6: ESP32 PWM speed and direction control through an L293-family driver.
# Report uses L293D; confirm the actual L293 suffix and module connections.
# Fixed the report's missing Pin/PWM import; control logic is preserved.
from machine import Pin, PWM
import time
# ESP32 + L293D + DC MOTOR
# GPIO22 -> EN1  : PWM / Speed
# GPIO21 -> IN1  : Direction
# GPIO18 -> IN2  : Direction
# PWM
EN1 = PWM(Pin(22), freq=1000, duty_u16=0)
# Direction pins
IN1 = Pin(21, Pin.OUT)
IN2 = Pin(18, Pin.OUT)
# MOTOR CONTROL FUNCTIONS
def stop_motor():
    EN1.duty_u16(0)
    IN1.value(0)
    IN2.value(0)
    print("Motor STOPPED")
def set_speed(percent):
    # Keep speed between 0 and 100
    if percent < 0:
        percent = 0
    if percent > 100:
        percent = 100
    duty = int((percent / 100) * 65535)
    EN1.duty_u16(duty)
    print("Speed:", percent, "%")
def forward(speed):
    # Stop PWM before changing direction
    EN1.duty_u16(0)
    IN1.value(1)
    IN2.value(0)
    # Apply requested speed
    set_speed(speed)
    print("Direction: FORWARD")
def reverse(speed):
    # Stop PWM before changing direction
    EN1.duty_u16(0)
    IN1.value(0)
    IN2.value(1)
    # Apply requested speed
    set_speed(speed)
    print("Direction: REVERSE")
# STARTUP
stop_motor()
print()
print("================================")
print(" ESP32 PWM MOTOR CONTROL")
print("================================")
print("PWM Frequency : 1000 Hz")
print()
print("Commands:")
print("f = Forward")
print("r = Reverse")
print("s = Stop")
print("1 = 10% speed")
print("2 = 25% speed")
print("3 = 50% speed")
print("4 = 75% speed")
print("5 = 90% speed")
print("x = Exit")
print()
# Default state
current_direction = "stop"
current_speed = 50
# USER CONTROL
while True:
    command = input("Enter command: ").strip().lower()
    # FORWARD
    if command == "f":
        forward(current_speed)
        current_direction = "forward"
    # REVERSE
    elif command == "r":
        reverse(current_speed)
        current_direction = "reverse"
    # STOP
    elif command == "s":
        stop_motor()
        current_direction = "stop"
    # SPEED = 10%
    elif command == "1":
        current_speed = 10
        if current_direction == "forward":
            forward(current_speed)
        elif current_direction == "reverse":
            reverse(current_speed)
        else:
            print("Speed set to 10%. Motor is stopped.")
    # SPEED = 25%
    elif command == "2":
        current_speed = 25
        if current_direction == "forward":
            forward(current_speed)
        elif current_direction == "reverse":
            reverse(current_speed)
        else:
            print("Speed set to 25%. Motor is stopped.")
    # SPEED = 50%
    elif command == "3":
        current_speed = 50
        if current_direction == "forward":
            forward(current_speed)
        elif current_direction == "reverse":
            reverse(current_speed)
        else:
            print("Speed set to 50%. Motor is stopped.")
    # SPEED = 75%
    elif command == "4":
        current_speed = 75
        if current_direction == "forward":
            forward(current_speed)
        elif current_direction == "reverse":
            reverse(current_speed)
        else:
            print("Speed set to 75%. Motor is stopped.")
    # SPEED = 90%
    elif command == "5":
        current_speed = 90
        if current_direction == "forward":
            forward(current_speed)
        elif current_direction == "reverse":
            reverse(current_speed)
        else:
            print("Speed set to 90%. Motor is stopped.")
    # EXIT
    elif command == "x":
        stop_motor()
        print("Program ended.")
        break
    else:
        print("Invalid command.")
        print("Use: f, r, s, 1, 2, 3, 4, 5, x")
