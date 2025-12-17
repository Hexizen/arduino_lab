import serial
import time

arduino_port = "COM7"
baud_rate = 9600

ser = serial.Serial(arduino_port, baud_rate)
time.sleep(2)

print("Connection Established. Reading button state...")

# ... setup code ...
print("Debug Mode: Reading raw bytes...")

while True:
    if ser.in_waiting > 0:
        # Read raw bytes without decoding
        raw_data = ser.readline()
        print(f"Raw data received: {raw_data}")

# try:
#     while True:
#         if ser.in_waiting > 0:
#             data = ser.readline().decode('utf-8').strip()
#             if data:
#                 command = None

#                 if data == "R":
#                     command = '1'
#                 elif data == "G":
#                     command = '2'
#                 elif data =="B":
#                     command = '3'

#                 if command:
#                     ser.write(command.encode())
#                     print(f"   -> Sent back: '{command}'")

#         time.sleep(0.01)

# except KeyboardInterrupt:
#     print("\nExiting...")
# finally:
#     ser.close()
