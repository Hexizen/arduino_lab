from fastapi import FastAPI, HTTPException
import serial
import time
import threading

# -----------------------------
# SERIAL CONFIGURATION
# -----------------------------
SERIAL_PORT = "COM7"  # 🔴 Change this to your Arduino port (e.g. COM4, /dev/ttyUSB0)
BAUD_RATE = 9600

try:
    arduino = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=1)
    time.sleep(2)  # Allow Arduino to reset
except:
    arduino = None
    print("⚠️ Arduino not connected")

# -----------------------------
# FASTAPI APP
# -----------------------------
app = FastAPI(title="Arduino LED Control API")

# -----------------------------
# HELPER FUNCTION
# -----------------------------
def send_to_arduino(command: str):
    if arduino and arduino.is_open:
        arduino.write(command.encode())
        time.sleep(0.1)
    else:
        raise HTTPException(status_code=500, detail="Arduino not connected")

# -----------------------------
# API ROUTES
# -----------------------------
@app.get("/led/on")
def turn_all_on():
    send_to_arduino("o") 
    return {"message": "All LEDs turned ON"}

@app.get("/led/off")
def turn_all_off():
    send_to_arduino("f") 
    return {"message": "All LEDs turned OFF"}

@app.get("/led/{color}")
def control_led(color: str):
    color = color.lower()

    if color == "red":
        send_to_arduino("1")
        return {"message": "Red LED toggled"}
    elif color == "green":
        send_to_arduino("2")
        return {"message": "Green LED toggled"}
    elif color == "blue":
        send_to_arduino("3")
        return {"message": "Blue LED toggled"}
    else:
        raise HTTPException(status_code=400, detail="Invalid color. Use red, green, or blue.")

# -----------------------------
# OPTIONAL: READ FROM ARDUINO
# -----------------------------
def read_from_arduino():
    while True:
        if arduino and arduino.in_waiting:
            data = arduino.readline().decode().strip()
            if data:
                print(f"Arduino says: {data}")

# Start background serial reader
if arduino:
    thread = threading.Thread(target=read_from_arduino, daemon=True)
    thread.start()