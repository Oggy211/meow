# EXP10: soil ADC reading and watering alert over BLE.
# AO connects to GPIO34; calibrate the threshold with your actual sensor.
import bluetooth
import time
from machine import Pin, ADC
from micropython import const
# SOIL MOISTURE SENSOR
sensor = ADC(Pin(34))
sensor.atten(ADC.ATTN_11DB)
# Adjust this after testing your sensor
DRY_THRESHOLD = 3000
# Assumption: higher ADC value means drier soil.
# Verify this with your actual sensor.
# BLE CONFIGURATION
_IRQ_CENTRAL_CONNECT = const(1)
_IRQ_CENTRAL_DISCONNECT = const(2)
SERVICE_UUID = bluetooth.UUID(
    "12345678-1234-5678-1234-56789abcdef0"
)
MOISTURE_UUID = bluetooth.UUID(
    "12345678-1234-5678-1234-56789abcdef1"
)
STATUS_UUID = bluetooth.UUID(
    "12345678-1234-5678-1234-56789abcdef2"
)
READ_NOTIFY = bluetooth.FLAG_READ | bluetooth.FLAG_NOTIFY
ble = bluetooth.BLE()
ble.active(True)
ble.config(gap_name="ESP32-Soil")
connections = set()
service = (
    SERVICE_UUID,
    (
        (MOISTURE_UUID, READ_NOTIFY),
        (STATUS_UUID, READ_NOTIFY),
    ),
)
((moisture_handle, status_handle),) = (
    ble.gatts_register_services((service,))
)
# ADVERTISING
def advertising_payload(name):
    name_bytes = name.encode()
    return (
        b"\x02\x01\x06"
        + bytes((len(name_bytes) + 1, 0x09))
        + name_bytes
    )
# BLE EVENT HANDLER
def ble_irq(event, data):
    if event == _IRQ_CENTRAL_CONNECT:
        conn_handle, addr_type, addr = data
        connections.add(conn_handle)
        print("LightBlue connected")
    elif event == _IRQ_CENTRAL_DISCONNECT:
        conn_handle, addr_type, addr = data
        connections.discard(conn_handle)
        print("LightBlue disconnected")
        ble.gap_advertise(
            100000,
            adv_data=advertising_payload("ESP32-Soil")
        )
ble.irq(ble_irq)
# START BLE
ble.gap_advertise(
    100000,
    adv_data=advertising_payload("ESP32-Soil")
)
print("BLE Soil Monitoring Started")
print("Device: ESP32-Soil")
print("Waiting for LightBlue...")
# MAIN LOOP
while True:
    raw_value = sensor.read()
    if raw_value >= DRY_THRESHOLD:
        status = "WATER REQUIRED"
    else:
        status = "WATER NOT REQUIRED"
    moisture_bytes = str(raw_value).encode()
    status_bytes = status.encode()
    # Store latest values for Read
    ble.gatts_write(moisture_handle, moisture_bytes)
    ble.gatts_write(status_handle, status_bytes)
    print("Soil ADC:", raw_value)
    print("Decision:", status)
    print("--------------------------")
    # Notify connected phone
    for conn_handle in tuple(connections):
        try:
            ble.gatts_notify(
                conn_handle,
                moisture_handle,
                moisture_bytes
            )
            ble.gatts_notify(
                conn_handle,
                status_handle,
                status_bytes
            )
        except OSError as error:
            print("BLE notification error:", error)
    time.sleep(2)
