import serial
import time

arduino_port = "COM4"
baud_rate = 9600

ser = serial.Serial(arduino_port, baud_rate)
time.sleep(2)

print("Connection Established. Reading button state...")

try:
    while True:
        if ser.in_waiting > 0:
            data = ser.readline().decode('utf-8').strip().upper()
            if data:
                command = None

                if data == "R":
                    command = '1'
                elif data == "G":
                    command = '2'
                elif data =="B":
                    command = '3'

                if command:
                    ser.write(command.encode())
                    print(f"   -> Sent back: '{command}'")

        time.sleep(0.01)

except KeyboardInterrupt:
    print("\nExiting...")
finally:
    ser.close()
